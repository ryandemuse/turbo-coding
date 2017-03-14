//
//  3paramsrand.c
//  
//
//  Created by Ryan DeMuse on 3/6/17.
//
//

#include "3paramsrand.h"

int * PERMUTATION;

int standard(int x) {
    return abs(x);
}

int circle(int x) {
    return (x > N - x) ? (N-x) : x;
}

int * permutation_generator(int s1, int s2, int s3) {
    int retarray = calloc(N,sizeof(int));
    int index = 0;
    
    return retarray;
}


int main() {
    
    PERMUTATION = permutation_generator(4,15,20);
    
    return 0;
}
