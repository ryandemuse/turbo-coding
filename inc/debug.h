//
//  debug.h
//  
//
//  Created by Ryan DeMuse on 2/8/17.
//
//

#ifndef debug_h
#define debug_h


// Debug an integer array
void DEBUG_int(int *array, int length);

// Debug a double array
void DEBUG_double(double *array, int length);

// Determine if value appears in permutation list
int in_list(int *array, int length, int j);

// Determine how far off two lists are
int listcmp(int *arr1, int *arr2, int length);

// Generate Random Length N binary vector
void rand_bin_vec(int *array, int length);

// Generate Random Length N interleaver permuation
void permutation_gen(int *array, int length);

// Puncture a Code to increase the Rate
// Ex: Puncture a Rate (1/3) to make it Rate (1/2)
void puncture(double *p, double *q, int length, int disp);


void puncture_3(double *p, double *q, double *r, int length, int disp);

#endif /* debug_h */
