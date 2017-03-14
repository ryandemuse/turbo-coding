//
//  turbo.h
//  
//
//  Created by Ryan DeMuse on 2/8/17.
//
//

#ifndef turbo_h
#define turbo_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "debug.h"
#include "channel.h"
#include "encoder.h"
#include "decoder.h"
#include "encoder4.h"
#include "decoder4.h"
#include "encoders3.h"
#include "decoders3.h"
#include "srandominterleaver.h"

// Encoder to be emulated is on page 493 of SKLAR

// Define constants to be used
#define N           400                                     // Length of input
#define M           4                                       // Number of Trellis States encoder (3)
#define M8          8                                       // Number of Trellis States encoder  4
#define TB          -1                                      // trellis termination bits
#define DEBUG       0                                       // set debug visibility
#define DEC_ITER    4                                       // Number of Decoder Iterations
#define TEST_LOOP   100000                                    // Number of Test Loop Iterations
#define SGN(x)      (x > 0) ? 1 : ((x < 0) ? -1 : 0)        // macro for sign function
#define MAX(x,y)    (x >= y) ? x : y                        // macro for max function
#define MIN(x,y)    (x > y) ? y : x

extern double sigma;            //variance of the channel AWGN

extern int* S_RAND_PERMUTATION;
extern int* primes;
extern int* coprimenums;
extern int* alpha_list;

extern int next[M][2];			//next[m][i] = next state (FROM state m with databit = i)
extern int prev[M][2];			//prev[m][i] = previous state (TO state m with databit = i)
extern int parity[M][2];		//parity bit associated with transition from state m
extern int term[M][2];			//term[m] = pair of data bits required to terminate trellis

extern int next_4[M8][2];			//next[m][i] = next state (FROM state m with databit = i)
extern int prev_4[M8][2];			//prev[m][i] = previous state (TO state m with databit = i)
extern int parity_4[M8][2];		//parity bit associated with transition from state m
extern int term_4[M8][3];			//term[m] = pair of data bits required to terminate trellis


#endif /* turbo_h */
