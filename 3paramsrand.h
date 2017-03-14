//
//  3paramsrand.h
//  
//
//  Created by Ryan DeMuse on 3/6/17.
//
//

#ifndef _paramsrand_h
#define _paramsrand_h

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define N   500     // length of permutation

int standard(int x);
int circle(int x);
int * permutation_generator(int s1, int s2, int s3);

#endif /* _paramsrand_h */
