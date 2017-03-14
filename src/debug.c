//
//  debug.c
//  
//
//  Created by Ryan DeMuse on 2/8/17.
//
//

#include "turbo.h"

void DEBUG_int(int *array, int length) {
    printf("\n");
    for(int i = 0; i < length; i++) {
        printf("array[%d] = %d\n",i,array[i]);
    }
    printf("\n");
    return;
}

void DEBUG_double(double *array, int length) {
    printf("\n");
    for(int i = 0; i < length; i++) {
        printf("array[%d] = %f\n",i,array[i]);
    }
    printf("\n");
    return;
}


int in_list(int *array, int length, int j) {
    int q;
    for(q = 0; q < N; q++) {
        if(array[q] == j) {return 1;}
    }
    return 0;
}


int listcmp(int *arr1, int *arr2, int length) {
    int temp = 0, n;
    for(n = 0; n < length; n++) {
        if(arr1[n] != arr2[n]) {
            temp++;
        }
    }
    return temp;
}


//
void rand_bin_vec(int *array, int length) {
    int n;
    srand(time(NULL));
    for(n = 0; n < length; n++) {
        array[n] = rand() % 2;
    }
    return;
}


// Generate Random Length N interleaver permuation
void permutation_gen(int *array, int length) {
    int k, l, temp;
    // init rand num gen with time so it produces a
    // different output on every run
    // if same output desired, init with: srand(1);
    srand(time(NULL));
    for(l = 0; l < length; l++) {array[l] = -1;}
    for(k = 0; k < length; k++) {
        do{
            temp = rand() % length;
        } while(in_list(array,length,temp) == 1);
        array[k] = temp;
    }
}


//
void puncture(double *p, double *q, int length, int disp) {
    int n, j;
    for(n = 0; n < length; n+=(disp+1)) {
        for(j = 0; j < disp; j++) {
            p[n+j] = 0;
            q[n+j+1] = 0;
        }
    }
    return;
}


//
void puncture_3(double *p, double *q, double *r, int length, int disp) {
    int n, j;
    for(n = 0; n < length; n+=(disp+2)) {
        for(j = 0; j < disp; j++) {
            p[n+j] = 0;
            q[n+j+1] = 0;
            r[n+j+2] = 0;
        }
    }
    return;
}
