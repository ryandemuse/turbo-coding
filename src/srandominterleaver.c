//
//  srandominterleaver.c
//  
//
//  Created by Ryan DeMuse on 2/23/17.
//
//

//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//#include "srandominterleaver.h"

#include "turbo.h"

int *primes;
int *coprimenums;
int *alpha_list;
int *S_RAND_PERMUTATION;

int * primeFactors(int n) {
    int *primefactors = malloc((sizeof(int))*n);
    int index = 0;
    
    if(n % 2 == 0) {
        primefactors[index] = 2;
        index++;
    }
    while(n % 2 == 0) {
        n = n/2;
    }
    
    for(int i = 3; i <= sqrt(n); i = i + 2) {
        if(n % i == 0) {
            primefactors[index] = i;
            index++;
        }
        while(n % i == 0) {
            n = n/i;
        }
    }
    
    if(n > 2) {
        primefactors[index] = n;
        index++;
    }
    primefactors[index] = -1;
    
    return primefactors;
}





int * coprimes(int n) {
    int array[n];
    int *retarray = malloc((sizeof(int))*n);
    int tempprimes[n];
    int index = 0;
    int length = 0;
    int prime;
    for(int i = 0; i <= n; i++) {
        array[i] = i;
    }
    while(primes[index] != -1) {
        tempprimes[index] = primes[index];
        index++;
    }
    tempprimes[index] = -1;
    length = index;
    index = 0;
    while(index < length) {
        prime = primes[index];
        for(int i = 0; i*prime <= n; i++) {
            array[i*prime] = 0;
        }
        index++;
    }
    index = 0;
    int indexret = 0;
    while(index <= n) {
        if(array[index] != 0) {
            retarray[indexret] = array[index];
            indexret++;
        }
        index++;
    }
    retarray[indexret] = -1;
    return retarray;
}



int * alphalistGen(int n) {
    int *retarray = malloc((sizeof(int))*n);
    int index = 0;
    int indexret = 0;
    int alpha;
    while(coprimenums[index] != -1) {
        alpha = coprimenums[index];
        if((alpha > 2) && (alpha < sqrt(n)) && (n % (alpha - 1) == 0)) {
            retarray[indexret] = alpha;
            indexret++;
        }
        index++;
    }
    retarray[indexret] = -1;
    
    return retarray;
}


int * SRandomPermutation(int n) {
    int *retarray = malloc((sizeof(int))*n);
    int alpha = 0;
    int beta = 0;
    int S1 = 0;
    int S2 = 0;
    int index = 0;
    while(alpha_list[index] != -1) {
        if(alpha_list[index] > alpha) {
            alpha = alpha_list[index];
        }
        index++;
    }
    S1 = MIN(alpha, (int) floor((double) n/(alpha+1)));
    S2 = (int) floor((double) (alpha-1)/2);
    beta = S2;
    index = 0;
    while(index < n) {
        retarray[index] = (alpha*index + beta) % n;
        index++;
    }
    return retarray;
}

void SRAND(int n) {
    primes = primeFactors(n);
    coprimenums = coprimes(n);
    alpha_list = alphalistGen(n);
    S_RAND_PERMUTATION = SRandomPermutation(n);
}


//int main() {
//    
//    int n = 3000;
//    
//    primes = primeFactors(n);
//    coprimenums = coprimes(n);
//    alpha_list = alphalistGen(n);
//    S_RAND_PERMUTATION = SRandomPermutation(n);
//    
//    int index = 0;
//    while(primes[index] != -1) {
//        printf("primes[%d] = %d\n", index, primes[index]);
//        index++;
//    }
//    
//    index = 0;
//    while(coprimenums[index] != -1) {
//        printf("coprimes[%d] = %d\n", index, coprimenums[index]);
//        index++;
//    }
//    
//    index = 0;
//    while(alpha_list[index] != -1) {
//        printf("alpha_list[%d] = %d\n", index, alpha_list[index]);
//        index++;
//    }
//    
//    
//    int arr[n];
//    int perm_arr[n];
//    index = 0;
//    while(index < n) {
//        arr[index] = index;
//        index++;
//    }
//    index = 0;
//    while(index < n) {
//        perm_arr[index] = arr[S_RAND_PERMUTATION[index]];
//        index++;
//    }
//    index = 0;
//    while(index < n) {
//        printf("perm_arr[%d] = %d\n", index, perm_arr[index]);
//        index++;
//    }
//    
//    return 0;
//}

