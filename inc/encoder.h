//
//  encoder.h
//
//  Created by Ryan DeMuse on 2/8/17.
//
//

/*
 This encoder architecture is given in the diagrams below. 
 It is a recursive systematic convolutional encoder.
 Rate = 1/3
 */

#ifndef encoder_h
#define encoder_h

// Generates the State Transition Table for the Encoder
//
//      +--------------------------> Xk
//      |  fb
//      |  +---------------+--------+
//      |  |               |        |
//  Xk--+-(+)--->[D]----->[D]----->[D]
//                |                 |
//                +-------(+)-------+
//						   |
//						   +-------> Pk
//
void table_gen(void);


//
//         +-----------> X[k]
//         |
//         |
//         |
//  X{k}---+--{E1}-----> P1[k]
//         |
//       {INT}
//         |
//         +--{E2}-----> P2[k]
//
//
void turbo_encode(int length, int *X, int *P1, int *P2, int *permutation);

#endif /* encoder_h */
