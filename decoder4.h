//
//  decoder4.h
//  
//
//  Created by Ryan DeMuse on 2/9/17.
//
//

#ifndef decoder4_h
#define decoder4_h

void turbo_decode_4(int length, double *x_n, double *p1_n, double *p2_n, double *L_h, int *X_h, int *permutation);

// Modified BCJR Algorithm for Turbo Decoding
void BCJR_4(int term, double Lc, int length, double *Lap, double *LLout, double *x_n, double *p_n);

#endif /* decoder4_h */
