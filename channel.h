//
//  channel.h
//  
//
//  Created by Ryan DeMuse on 2/8/17.
//
//

#ifndef channel_h
#define channel_h

// Normal Distribution for AWGN
double normal(void);

// Additive White Gaussian Noise for Channel Simulation
void AWGN(int length, double *x, double *p1, double *p2, double *p3, double *x_n, double *p1_n, double *p2_n, double *p3_n);

// Map data bits to channel symbols
void symbol_map(int length, double *x, int *X, double *p1, int *P1, double *p2, int *P2, double *p3, int *P3);

#endif /* channel_h */
