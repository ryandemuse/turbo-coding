//
//  encoders3.c
//  
//
//  Created by Ryan DeMuse on 2/12/17.
//
//

#include "turbo.h"


void turbo_encoders_3(int length, int *X, int *P1, int *P2, int *P3, int *permutation_1, int *permutation_2) {
    
    int k;              // trellis stage
    int state;          // encoder state
    int X_p12[length];	// permuted X (1 --> 2)
    int X_p13[length];  // permuted X (1 --> 3)
    
    // encoder #1
    state = 0;
    for(k = 0; k < length-3; k++) {
        P1[k] = parity_4[state][X[k]];
        state = next_4[state][X[k]];
    }
    
    // terminate encoder #1 trellis to state 0
    X[length-3] = term_4[state][0];
    X[length-2] = term_4[state][1];
    X[length-1] = term_4[state][2];
    
    P1[length-3] = parity_4[state][X[length-3]];
    state = next_4[state][X[length-3]];
    P1[length-2] = parity_4[state][X[length-2]];
    state = next_4[state][X[length-2]];
    P1[length-1] = parity_4[state][X[length-1]];
    state = next_4[state][X[length-1]];
    
//    if(state != 0) {
//        printf("Error: could not terminate encoder 1\n");
//        exit(1);
//    }
    
    // permute data bits for encoder 2 and encoder 3
    for(k = 0; k < length; k++) {
        X_p12[k] = X[permutation_1[k]];
        X_p13[k] = X[permutation_2[k]];
    }
    
    // encoder #2
    state = 0;
    for(k = 0; k < length; k++) {
        P2[k] = parity_4[state][X_p12[k]];
        state = next_4[state][X_p12[k]];
    }
    
    // encoder #3
    state = 0;
    for(k = 0; k < length; k++) {
        P3[k] = parity_4[state][X_p13[k]];
        state = next_4[state][X_p13[k]];
    }
    
    return;
}
