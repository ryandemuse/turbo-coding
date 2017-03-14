//
//  encoders3.h
//  
//
//  Created by Ryan DeMuse on 2/12/17.
//
//

#ifndef encoders3_h
#define encoders3_h

//
//            +-----------> X[k]
//            |
//            |
//            |
//  X{k}--+---+--{E1}-----> P1[k]
//        |   |
//        | {INT1}
//        |   |
//        |   +--{E2}-----> P2[k]
//        |
//      {INT2}
//        |
//        +------{E3}-----> P3[k]
//
void turbo_encoders_3(int length, int *X, int *P1, int *P2, int *P3, int *permutation_1, int *permutation_2);

#endif /* encoders3_h */
