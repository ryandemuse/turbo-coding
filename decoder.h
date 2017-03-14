//
//  decoder.h
//  
//
//  Created by Ryan DeMuse on 2/8/17.
//
//

#ifndef decoder_h
#define decoder_h

void turbo_decode(int length, double *x_n, double *p1_n, double *p2_n, double *L_h, int *X_h, int *permutation);

// Modified BCJR Algorithm for Turbo Decoding
void BCJR(int term, double Lc, int length, double *Lap, double *LLout, double *x_n, double *p_n);

#endif /* decoder_h */
