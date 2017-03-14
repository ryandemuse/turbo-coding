//
//  encoder4.h
//  
//
//  Created by Ryan DeMuse on 2/9/17.
//
//

/*
 This encoder architecture is given in the diagrams below.
 It is a recursive systematic convolutional encoder.
 Rate = 1/3
 */

#ifndef encoder4_h
#define encoder4_h


// Generates the State Transition Table for the Encoder
//
//      +------------------------------------------> Xk
//      |  fb
//      |  +------+--------+--------+--------+
//      |  |      |        |        |        |
//  Xk--+-(+)--->[D]----->[D]----->[D]----->[D]
//                |                          |
//                +------------(+)-----------+
//						        |
//						        +------------------> Pk
//
void table_gen_4(void);


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
void turbo_encode_4(int length, int *X, int *P1, int *P2, int *permutation);

#endif /* encoder4_h */
