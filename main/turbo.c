//
//  turbo.c
//  
//
//  Created by Ryan DeMuse on 2/8/17.
//
//

#include "turbo.h"


int main(int argc, char **argv) {
    
//    int k;
    
    // *******************
    int X[N]; //= {0,0,0,0,0,0,TB,TB};
    int Y[N];
    int Z[N];
    // *******************
    
//    for(k = 0; k < N - 2; k++) {
//        X[k] = 1;
//    }
//    
//    for(k = 0; k < N - 3; k++) {
//        Y[k] = 1;
//    }
//    
//    for(k = 0; k < N - 3; k++) {
//        Z[k] = 1;
//    }
    
    // May want to change the previous line and following array lines
    // so that the arrays are allocated on the HEAP instead of the stack
    // in order to avoid memory problems if the arrays become longer
    
    int permutation[N];
    int permutation_2[N];
    
    int 	P1[N];          // encoder #1 parity bits
    int 	P2[N];          // encoder #2 parity bits
    int     P3[N];          // encoder #3 parity bits (if using encoders3.c)
    double	x[N];           // data mapped to symbols for channel
    double	p1[N];          // encoder #1 parity bit mapped to symbol for channel
    double  p2[N];          // encoder #2 parity bit " " " "
    double  p3[N];          // encoder #3 parity bit " " " "
    double  x_n[N];         // noisy data
    double  p1_n[N];        // noisy parity #1
    double  p2_n[N];        // noisy parity #2
    double  p3_n[N];        // noisy parity #3
    double  L_h[N];
    int     X_h[N];
//    
//    srand(time(NULL));
//    
//    table_gen();
//    permutation_gen(permutation,N);
//    turbo_encode(N, X, P1, P2, permutation);
//    symbol_map(N, x,X,p1,P1,p2,P2,NULL,NULL);
//    AWGN(N,x,p1,p2,NULL,x_n,p1_n,p2_n,NULL);
//    //puncture(p1_n,p2_n,N,2);
//    turbo_decode(N, x_n,p1_n,p2_n,L_h,X_h, permutation);
//    
//    
//    
//    printf("Received Data:\n\n");
//    DEBUG_int(X,N);
//    printf("Noisy Data:\n\n");
//    DEBUG_double(x_n,N);
//    printf("Noisy Parity 1:\n\n");
//    DEBUG_double(p1_n,N);
//    printf("Noisy Parity 2:\n\n");
//    DEBUG_double(p2_n,N);
//    printf("Soft Decisions after Decoding:\n\n");
//    DEBUG_double(L_h,N);
//    printf("Hard Decisions from Decoding:\n\n");
//    DEBUG_int(X_h,N);
//    
//    
//    printf("\n\n NOW THE NEXT ENCODER AND DECODER \n\n");
//    
//    
//    table_gen_4();
//    turbo_encode_4(N, Y, P1, P2, permutation);
//    symbol_map(N, x, Y, p1, P1, p2, P2, NULL, NULL);
//    AWGN(N,x,p1,p2,NULL,x_n,p1_n,p2_n,NULL);
//    puncture(p1_n,p2_n,N,1);
//    turbo_decode_4(N, x_n, p1_n, p2_n, L_h, X_h, permutation);
//    
//    
//    printf("Received Data:\n\n");
//    DEBUG_int(Y,N);
//    printf("Noisy Data:\n\n");
//    DEBUG_double(x_n,N);
//    printf("Noisy Parity 1:\n\n");
//    DEBUG_double(p1_n,N);
//    printf("Noisy Parity 2:\n\n");
//    DEBUG_double(p2_n,N);
//    printf("Soft Decisions after Decoding:\n\n");
//    DEBUG_double(L_h,N);
//    printf("Hard Decisions from Decoding:\n\n");
//    DEBUG_int(X_h,N);
//
//    printf("\n\n NOW THE NEXT ENCODER AND DECODER \n\n");
//    
//    permutation_gen(permutation_2,N);
//    turbo_encoders_3(N, Y, P1, P2, P3, permutation, permutation_2);
//    symbol_map(N,x,Y,p1,P1,p2,P2,p3,P3);
//    AWGN(N,x,p1,p2,p3,x_n,p1_n,p2_n,p3_n);
//    puncture_3(p1_n,p2_n,p3_n,N,2);
//    turbo_decode_3(N,x_n,p1_n,p2_n,p3_n,L_h,X_h,permutation,permutation_2);
//    
//    printf("Received Data:\n\n");
//    DEBUG_int(Y,N);
//    printf("Noisy Data:\n\n");
//    DEBUG_double(x_n,N);
//    printf("Noisy Parity 1:\n\n");
//    DEBUG_double(p1_n,N);
//    printf("Noisy Parity 2:\n\n");
//    DEBUG_double(p2_n,N);
//    printf("Noisy Parity 3:\n\n");
//    DEBUG_double(p3_n,N);
//    printf("Soft Decisions after Decoding:\n\n");
//    DEBUG_double(L_h,N);
//    printf("Hard Decisions from Decoding:\n\n");
//    DEBUG_int(X_h,N);
    
    
    //
    //  CUMULATIVE LOOP TESTING OF ENCODER/DECODER ARCHITECTURE
    //
    
    int index = 0;
    int total1 = 0, total2 = 0, total3 = 0;
    
    srand(time(NULL));
    
    permutation_gen(permutation,N);
    permutation_gen(permutation_2, N);
    
    SRAND(N);
    
    table_gen();
    table_gen_4();
    
    while(index < TEST_LOOP) {
        
        //
        // ARCHITECTURE 1
        //
        
        rand_bin_vec(X,N-2);
        X[N-2] = TB;
        X[N-1] = TB;

        turbo_encode(N, X, P1, P2, permutation);
        //turbo_encode(N, X, P1, P2, S_RAND_PERMUTATION);
        symbol_map(N, x,X,p1,P1,p2,P2,NULL,NULL);
        AWGN(N,x,p1,p2,NULL,x_n,p1_n,p2_n,NULL);
        //puncture(p1_n,p2_n,N,1);
        turbo_decode(N, x_n,p1_n,p2_n,L_h,X_h, permutation);
        //turbo_decode(N, x_n,p1_n,p2_n,L_h,X_h, S_RAND_PERMUTATION);
        
        total1 += listcmp(X,X_h,N-2);
        
        
        
        
//        //
//        //  ARCHITECTURE 2
//        //
//        
//        rand_bin_vec(Y,N-3);
//        Y[N-3] = TB;
//        Y[N-2] = TB;
//        Y[N-1] = TB;
//        
//        turbo_encode_4(N, Y, P1, P2, S_RAND_PERMUTATION);
//        symbol_map(N, x, Y, p1, P1, p2, P2, NULL, NULL);
//        AWGN(N,x,p1,p2,NULL,x_n,p1_n,p2_n,NULL);
//        //puncture(p1_n,p2_n,N,1);
//        turbo_decode_4(N, x_n, p1_n, p2_n, L_h, X_h, S_RAND_PERMUTATION);
//        
//        total2 += listcmp(Y,X_h,N-3);
//        
//        
//        
//        //
//        //  ARCHITECTURE 3
//        //
//        
//        rand_bin_vec(Z,N-3);
//        Z[N-3] = TB;
//        Z[N-2] = TB;
//        Z[N-1] = TB;
//
//        turbo_encoders_3(N, Z, P1, P2, P3, S_RAND_PERMUTATION, S_RAND_PERMUTATION);
//        symbol_map(N,x,Z,p1,P1,p2,P2,p3,P3);
//        AWGN(N,x,p1,p2,p3,x_n,p1_n,p2_n,p3_n);
//        //puncture_3(p1_n,p2_n,p3_n,N,2);
//        turbo_decode_3(N,x_n,p1_n,p2_n,p3_n,L_h,X_h,S_RAND_PERMUTATION,S_RAND_PERMUTATION);
//        
//        total3 += listcmp(Z,X_h,N-3);
        
        
        index++;
    }
    
    printf("\nBER for Architecture 1: %e\n", (float) total1/(N*TEST_LOOP));
    printf("\nBER for Architecture 2: %e\n", (float) total2/(N*TEST_LOOP));
    printf("\nBER for Architecture 3: %e\n\n", (float) total3/(N*TEST_LOOP));
    
    
//
//    
//    int r;
//    printf("Permutation of S(%d) used: ", N);
//    for(r = 0; r < N; r++) {
//        printf("%d ",permutation[r]);
//    }
//    printf("\n\n");
//    return 0;
}
