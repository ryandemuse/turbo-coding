//
//  decoders3.c
//  
//
//  Created by Ryan DeMuse on 2/12/17.
//
//

#include "turbo.h"


void turbo_decode_3(int length, double *x_n, double *p1_n, double *p2_n, double *p3_n, double *L_h, int *X_h, int *permutation_1, int *permutation_2) {
    
    int ni, n;
    double Lc;          // channel measure
    double Le1[length];      // decoder #1 extrinsic likelihood
    double Le1_p1[length];    // decoder #1 extrinsic likelihood permuted
    double Le2[length];      // decoder #2 extrinsic likelihood
    double Le2_ip1[length];
    double Le2_p2[length];   // decoder #2 extrinsic likelihood inverse permuted
    double Le3[length];
    double Le3_ip2[length];
    double LLout1[length];   // output LLR from BCJR decoder 1
    double LLout2[length];   // output LLR from BCJR decoder 2
    double LLout3[length];   // output LLR from BCJR decoder 3
    double x_np1[length];     // permuted input data 1
    double x_np2[length];     // permuted input data 2
    
    
    Lc = 2.0 / (sigma*sigma);
    
    for(n = 0; n < length; n++) {
        Le3_ip2[n] = 0.0;
        LLout1[n] = 0.0;
        LLout2[n] = 0.0;
        x_np1[n] = x_n[permutation_1[n]];
        x_np2[n] = x_n[permutation_2[n]];
    }
    
    
    // Iterations of the BCJR algorithm for two Encoder Architecture
    for(ni = 0; ni < DEC_ITER; ni++) {
        
        BCJR_4(0,Lc,N,Le3_ip2,LLout1,x_n,p1_n);
        
        for(n = 0; n < length; n++) {
            Le1[n] = LLout1[n] - Le3_ip2[n] - Lc*x_n[n];
        }
        for(n = 0; n < length; n++) {Le1_p1[n] = Le1[permutation_1[n]];}
        
        BCJR_4(0,Lc,N,Le1_p1,LLout2,x_np1,p2_n);
        
        for(n = 0; n < length; n++) {
            Le2[n] = LLout2[n] - Le1_p1[n] - Lc*x_np1[n];
        }
        
        for(n = 0; n < length; n++) {
            Le2_ip1[permutation_1[n]] = Le2[n];
            Le2_p2[n] = Le2_ip1[permutation_2[n]];
        }
        
        BCJR_4(0,Lc,N,Le2_p2,LLout3,x_np2,p3_n);
        
        for(n = 0; n < length; n++) {
            Le3[n] = LLout3[n] - Le2_p2[n] - Lc*x_np2[n];
        }
        
        for(n = 0; n < length; n++) {Le3_ip2[permutation_2[n]] = Le3[n];}
        
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
        L_h[n] = Lc*x_n[n] + Le1[n] + Le2_ip1[n] + Le3_ip2[n];
        X_h[n] = (L_h[n] > 0.0) ? 1 : 0;
    }
    
    return;
}
