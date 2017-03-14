//
//  channel.c
//  
//
//  Created by Ryan DeMuse on 2/8/17.
//
//

#include "turbo.h"

double sigma = 0.97;      // Noise Variance for Channel


// Normal Distribution Additive White Gaussian Noise
double normal(void) {
    double x, y, rr;
    do {
        x = (double) 2*rand()/RAND_MAX - 1.0;
        y = (double) 2*rand()/RAND_MAX - 1.0;
        rr = x*x + y*y;
    } while(rr >= 1);
    return x*sqrt((-2.0*log(rr))/rr);
}

// Additive White Gaussian Noise
void AWGN(
          int length,
          double *x,
          double *p1,
          double *p2,
          double *p3,
          double *x_n,
          double *p1_n,
          double *p2_n,
          double *p3_n) {
    
    for(int i = 0; i < length; i++) {
        x_n[i] = x[i] + sigma*normal();
        p1_n[i] = p1[i] + sigma*normal();
        p2_n[i] = p2[i] + sigma*normal();
        if(p3 != NULL) {
            p3_n[i] = p2[i] + sigma*normal();
        }
    }
    return;
}

// Map data bits to channel symbols
void symbol_map(
                int length,
                double *x,
                int *X,
                double *p1,
                int *P1,
                double *p2,
                int *P2,
                double *p3,
                int *P3) {
    
    for(int k = 0; k < length; k++) {
        x[k]  = 2*X[k] - 1;  //map databit to symbol
        p1[k] = 2*P1[k] - 1;  //map parity #1 to symbol
        p2[k] = 2*P2[k] - 1;  //map parity #2 to symbol
        if(P3 != NULL) {
            p3[k] = 2*P3[k] - 1;
        }
    }
    
    return;
}
