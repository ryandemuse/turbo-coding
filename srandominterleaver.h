//
//  srandominterleaver.h
//  
//
//  Created by Ryan DeMuse on 2/23/17.
//
//

#ifndef srandominterleaver_h
#define srandominterleaver_h

//#define MIN(x,y)    (x > y) ? y : x

// Find all prime factors of a given integer
// the returned array includes all prime factors and array terminates with -1 entry
int * primeFactors(int n);


// Find all numbers coprime to a given integer
// uses a sieve since we calculate the prime factors in primeFactors method
int * coprimes(int n);

// Generate sufficient coprime list for interleaver
int * alphalistGen(int n);

// Generate the S Random Permutation
int * SRandomPermutation(int n);

void SRAND(int n);

#endif /* srandominterleaver_h */
