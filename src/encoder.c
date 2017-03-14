//
//  encoder.c
//  
//
//  Created by Ryan DeMuse on 2/8/17.
//
//

#include "turbo.h"

int next[M][2];			//next[m][i] = next state (FROM state m with databit = i)
int prev[M][2];			//prev[m][i] = previous state (TO state m with databit = i)
int parity[M][2];		//parity bit associated with transition from state m
int term[M][2];			//term[m] = pair of data bits required to terminate trellis



// Generates the State Transition Table for the Encoder
void table_gen(void) {
    
    int m, i, b0, b1, fb, state;
    
    // generate tables for 4 state encoder
    for(m = 0; m < M; m++) {
        for(i = 0; i < 2; i++) {
            b0 = (m >> 0) & 1;	// bit 0 of state
            b1 = (m >> 1) & 1;	// bit 1 of state
            
            parity[m][i] = b0 ^ i;		// parity from state m with databit i
            
            next[m][i] = (b0 << 1) + (i ^ b0 ^ b1);
        }
    }
    
    for(m = 0; m < M; m++) {
        for(i = 0; i < 2; i++) {
            prev[next[m][i]][i] = m;
        }
    }
    
    // generate table of data bit pairs which terminate
    // the trellis for a given state m
    //
    // we set Xk equal to the feedback value to force
    // the delay line to fill up with zeros
    for(m = 0; m < M; m++) {
        state = m;
        b0 = (state >> 0) & 1;
        b1 = (state >> 1) & 1;
        fb = b0 ^ b1;
        term[m][0] = fb;
        
        state = next[m][fb];
        b0 = (state >> 0) & 1;
        b1 = (state >> 1) & 1;
        fb = b0 ^ b1;
        term[m][1] = fb;
    }
}



//
void turbo_encode(int length, int *X, int *P1, int *P2, int *permutation) {
    int k;		// trellis stage
    int state;	// encoder state
    int X_p[length];	// permuted X
    
    // encoder #1
    state = 0;
    for(k = 0; k < length-2; k++) {
        P1[k] = parity[state][X[k]];
        state = next[state][X[k]];
    }
    
    // terminate encoder #1 trellis to state 0
    X[length-2] = term[state][0];
    X[length-1] = term[state][1];
    
    P1[length-2] = parity[state][X[length-2]];
    state   = next[state][X[length-2]];
    P1[length-1] = parity[state][X[length-1]];
    state   = next[state][X[length-1]];
    
    if(state != 0) {
        printf("Error: could not terminate encoder 1\n");
        exit(1);
    }
    
    // permute data bits for encoder 2
    for(k = 0; k < length; k++) { X_p[k] = X[permutation[k]]; }
    
    // encoder #2
    state = 0;
    for(k = 0; k < length; k++) {
        P2[k] = parity[state][X_p[k]];
        state = next[state][X_p[k]];
    }
}


