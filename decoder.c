//
//  decoder.c
//  
//
//  Created by Ryan DeMuse on 2/8/17.
//
//

#include "turbo.h"



// Modified BCJR Algorithm for Turbo Decoding Procedure
void BCJR (
           int term,
           double Lc,
           int length,
           double *Lap,
           double *LLout,
           double *x_n,
           double *p_n) {
    
    
    int n,m;
    double x0 = -1.0, x1 = 1.0, p0, p1;
    double total;
    double PR1, PR0;
    double gamma[length][M][2];                  // branch transition probabilities
    double gamma_ex[length][M][2];               // branch extrinsic transition probs
    double alpha[length+1][M];                   // alpha state probabilities
    double beta[length+1][M];                    // beta state probabilities
    
    
    // initialize the alphas
    alpha[0][0] = 1.0;
    for(m = 1; m < M; m++) {alpha[0][m] = 0.0;}
    
    
    //
    //  CALCULATION OF THE GAMMA TRANSITION PROBABILITIES
    //
    for(n = 0; n < length; n++) {            // Loop through trellis time steps
        for(m = 0; m < M; m++) {        // Loop through states at each time step
            // Now proceed for each databit
            
            p0 = parity[m][0] ? 1.0 : -1.0;
            p1 = parity[m][1] ? 1.0 : -1.0;
            
            gamma[n][m][0] = exp(0.5*(Lap[n]*x0 + Lc*x_n[n]*x0 + Lc*p_n[n]*p0));
            gamma[n][m][1] = exp(0.5*(Lap[n]*x1 + Lc*x_n[n]*x1 + Lc*p_n[n]*p1));
            
            gamma_ex[n][m][0] = exp(0.5*(Lc*p_n[n]*p0));
            gamma_ex[n][m][1] = exp(0.5*(Lc*p_n[n]*p1));
        }
    }
    
    //
    //  CALCULATION OF THE ALPHA STATE PROBABILITIES
    //
    for(n = 1; n <= length; n++) {
        
        total = 0.0;
        
        for(m = 0; m < M; m++) {
            alpha[n][m] = alpha[n-1][prev[m][0]] * gamma[n-1][prev[m][0]][0] + alpha[n-1][prev[m][1]] * gamma[n-1][prev[m][1]][1];
            
            total += alpha[n][m];
        }
        
        for(m = 0; m < M; m++) {alpha[n][m] /= total;}
    }
    
    
    //
    //  CALCULATION OF THE BETA STATE PROBABILITIES
    //      ideally, the trellis has terminated to the 0 state
    //      if it has, assign beta's as they should be knowing 0 state has prob 1
    //      it it has not, assign all initial betas equally likely
    //
    if(term) {
        beta[length][0] = 1.0;
        for(m = 1; m < M; m++) {beta[length][m] = 0.0;}
    }
    else {
        for(m = 0; m < M; m++) {beta[length][m] = 1.0 / ((double) M);}
    }
    
    //  calculation of the reverse state probabilities
    for(n = length - 1; n >= 0; n--) {
        
        total = 0.0;
        
        for(m = 0; m < M; m++) {
            
            beta[n][m] = beta[n+1][next[m][0]] * gamma[n][m][0] + beta[n+1][next[m][1]] * gamma[n][m][1];
            
            total += beta[n][m];
        }
        
        // normalize at each time step
        for(m = 0; m < M; m++) {beta[n][m] /= total;}
    }
    
    
    //
    //  CALCULATE THE LOG LIKELIHOOD RATIOS
    //      now that all of the state and branch probabilities are
    //      calculated, we can calculate the LLR
    //
    for(n = 0; n < length; n++) {
        
        PR0 = PR1 = 0.0;
        
        for(m = 0; m < M; m++) {
            PR1 += alpha[n][m] * gamma[n][m][1] * beta[n+1][next[m][1]];
            PR0 += alpha[n][m] * gamma[n][m][0] * beta[n+1][next[m][0]];
            
            //PR1 += alpha[n][m] * gamma_ex[n][m][1] * beta[n+1][next[m][1]];
            //PR0 += alpha[n][m] * gamma_ex[n][m][0] * beta[n+1][next[m][0]];
        }
        LLout[n] = log(PR1/PR0);
    }
    
    return;
}



//
void turbo_decode(
                  int length,
                  double *x_n,
                  double *p1_n,
                  double *p2_n,
                  double *L_h,
                  int *X_h,
                  int *permutation)
{
    
    int ni, n;
    double Lc;          // channel measure
    double Le1[length];      // decoder #1 extrinsic likelihood
    double Le1_p[length];    // decoder #1 extrinsic likelihood permuted
    double Le2[length];      // decoder #2 extrinsic likelihood
    double Le2_ip[length];   // decoder #2 extrinsic likelihood inverse permuted
    double LLout1[length];   // output LLR from BCJR decoder 1
    double LLout2[length];   // output LLR from BCJR decoder 2
    double x_np[length];     // permuted input data
    
    
    Lc = 2.0 / (sigma*sigma);
    
    for(n = 0; n < length; n++) {
        Le2_ip[n] = 0.0;
        LLout1[n] = 0.0;
        LLout2[n] = 0.0;
        x_np[n] = x_n[permutation[n]];
    }
    
    
    // Iterations of the BCJR algorithm for two Encoder Architecture
    for(ni = 0; ni < DEC_ITER; ni++) {
        
        BCJR(1,Lc,N,Le2_ip,LLout1,x_n,p1_n);
        
        for(n = 0; n < length; n++) {
            Le1[n] = LLout1[n] - Le2_ip[n] - Lc*x_n[n];
        }
        for(n = 0; n < length; n++) {Le1_p[n] = Le1[permutation[n]];}
        
        BCJR(0,Lc,N,Le1_p,LLout2,x_np,p2_n);
        
        for(n = 0; n < length; n++) {
            Le2[n] = LLout2[n] - Le1_p[n] - Lc*x_np[n];
        }
        for(n = 0; n < length; n++) {Le2_ip[permutation[n]] = Le2[n];}
        
        for(n = 0; n < length; n++)
        {
            //printf("Le1[%i] = %f\t", n, Le1[n]);
            //printf("Le2_ip[%i] = %f\t", n, Le2_ip[n]);
            //printf("Lc*x_d[%i] = %f", k, Lc*x_d[k]);
            //printf("\n");
        }
        //printf("\n");
    }
    
    // Now calculate the soft decisions
    for(n = 0; n < length; n++) {
        L_h[n] = Lc*x_n[n] + Le1[n] + Le2_ip[n];
        X_h[n] = (L_h[n] > 0.0) ? 1 : 0;
    }
    
    return;
}
