//
//  encoder4.c
//  
//
//  Created by Ryan DeMuse on 2/9/17.
//
//

/*
 
        CHANGE THIS TO REMOVE THE FEEDBACK
 
        ALSO BUILD A 16 AND 32 STATE ENCODER 
 
 */

#include "turbo.h"

// #include <stdio.h>
// #include <stdlib.h>

// const int M8 = 8;

int next_4[M8][2];			//next[m][i] = next state (FROM state m with databit = i)
int prev_4[M8][2];			//prev[m][i] = previous state (TO state m with databit = i)
int parity_4[M8][2];		//parity bit associated with transition from state m
int term_4[M8][3];			//term[m] = pair of data bits required to terminate trellis


/*
 Table Generation Function for this 4 state encoder needs work.
 Need to figure out if the state transitions are correct.
 Also need to figure out how to terminate the trellis for a given state m.
 */
void table_gen_4(void) {
    int m, i, b0, b1, b2, fb, state;
    
    // generate tables for 8 state encoder
    for(m = 0; m < M8; m++) {
        for(i = 0; i < 2; i++) {
            b0 = (m >> 0) & 1;	// bit 0 of state
            b1 = (m >> 1) & 1;	// bit 1 of state
            b2 = (m >> 2) & 1;  // bit 2 of state
            
            parity_4[m][i] = b0 ^ i;		// parity from state m with databit i
            
            next_4[m][i] = (b0 << 1) + (b1 << 2) + (i ^ b0 ^ b1 ^ b2);
        }
    }
    
    for(m = 0; m < M8; m++) {
        for(i = 0; i < 2; i++) {
            prev_4[next_4[m][i]][i] = m;
        }
    }
    
    // generate table of data bit pairs which terminate
    // the trellis for a given state m
    //
    // we set Xk equal to the feedback value to force
    // the delay line to fill up with zeros
    for(m = 0; m < M8; m++) {
        state = m;
        b0 = (state >> 0) & 1;
        b1 = (state >> 1) & 1;
        b2 = (state >> 2) & 1;
        fb = b0 ^ b1 ^ b2;
        term_4[m][0] = fb;
        
        state = next_4[m][fb];
        b0 = (state >> 0) & 1;
        b1 = (state >> 1) & 1;
        b2 = (state >> 2) & 1;
        fb = b0 ^ b1 ^ b2;
        term_4[m][1] = fb;
        
        state = next_4[m][fb];
        b0 = (state >> 0) & 1;
        b1 = (state >> 1) & 1;
        b2 = (state >> 2) & 1;
        fb = b0 ^ b1 ^ b2;
        term_4[m][2] = fb;
    }
}



void turbo_encode_4(int length, int *X, int *P1, int *P2, int *permutation) {
    int k;		// trellis stage
    int state;	// encoder state
    int X_p[length];	// permuted X
    
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
    
    // permute data bits for encoder 2
    for(k = 0; k < length; k++) { X_p[k] = X[permutation[k]]; }
    
    // encoder #2
    state = 0;
    for(k = 0; k < length; k++) {
        P2[k] = parity_4[state][X_p[k]];
        state = next_4[state][X_p[k]];
    }
    
    
    return;
}



// Testing main for the functionality of the table generation
//int main(int argc, char **argv) {
//    
//    
//    table_gen_4();
//    
//    int m;
//    
//    printf("next_4 matrix:\n\n");
//    for(m = 0; m < M8; m++) {
//        printf("next_4[%d][%d] = %d \t next_4[%d][%d] = %d\n",m,0,next_4[m][0],m,1,next_4[m][1]);
//    }
//    printf("\n\n");
//    
//    
//    printf("prev_4 matrix:\n\n");
//    for(m = 0; m < M8; m++) {
//        printf("prev_4[%d][%d] = %d \t prev_4[%d][%d] = %d\n",m,0,prev_4[m][0],m,1,prev_4[m][1]);
//    }
//    printf("\n\n");
//    
//    
//    printf("parity_4 matrix:\n\n");
//    for(m = 0; m < M8; m++) {
//        printf("parity_4[%d][%d] = %d \t parity_4[%d][%d] = %d\n",m,0,parity_4[m][0],m,1,parity_4[m][1]);
//    }
//    printf("\n\n");
//    
//    
//    printf("term_4 matrix:\n\n");
//    for(m = 0; m < M8; m++) {
//        printf("term_4[%d][%d] = %d \t term_4[%d][%d] = %d \t term_4[%d][%d] = %d\n",m,0,term_4[m][0],m,1,term_4[m][1],m,2,term_4[m][2]);
//    }
//    printf("\n\n");
//
//    
//    return 0;
//}
