/*
 * -----------------------------------------------------------------
 * $Revision: 1.0 $
 * $Date: 2013/08/31 12:20:00 $
 * ----------------------------------------------------------------- 
 * Programmer(s): David J. Gardner @ LLNL
 * -----------------------------------------------------------------
 * Copyright (c) 2002, The Regents of the University of California.
 * Produced at the Lawrence Livermore National Laboratory.
 * All rights reserved.
 * For details, see the LICENSE file.
 * -----------------------------------------------------------------
 * This is the testing routine to check the POSIX Threads (Pthreads) 
 * NVECTOR module implementation which uses a LOCAL data struct to 
 * share data between threads. 
 * -----------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>

#include <sundials/sundials_types.h>
#include <nvector/nvector_pthreads.h>
#include <sundials/sundials_math.h>
#include <test_nvector.h>


/* ----------------------------------------------------------------------
 * Main NVector Testing Routine
 * --------------------------------------------------------------------*/
int main(int argc, char *argv[]) 
{
  int      fails = 0;  /* counter for test failures */
  int      nthreads;   /* number of threads         */
  long int veclen;     /* vector length             */
  N_Vector W, X, Y, Z; /* test vectors              */

  /* check inputs, set vector length, and number of threads */
  if (argc < 3){
    printf("ERROR: TWO (2) Inputs required: vector length, number of threads \n");
    return(-1);
  }

  veclen = atol(argv[1]); 
  if (veclen <= 0) {
    printf("ERROR: length of vector must be a positive integer \n");
    return(-1); 
  }

  nthreads = atoi(argv[2]);
  if (nthreads < 1) {
    printf("ERROR: number of threads must be at least 1 \n");
    return(-1); 
  }

  printf("\nRunning with %d threads and vector length %ld \n \n", nthreads, veclen);

  /* Create vectors */
  W = N_VNewEmpty_Pthreads(veclen, nthreads);
  X = N_VNew_Pthreads(veclen, nthreads);
  Y = N_VNew_Pthreads(veclen, nthreads);
  Z = N_VNew_Pthreads(veclen, nthreads);

  /* NVector Tests */
  fails += Test_N_VSetArrayPointer(W, veclen, 0);
  fails += Test_N_VGetArrayPointer(X, veclen, 0);
  fails += Test_N_VLinearSum(X, Y, Z, veclen, 0);
  fails += Test_N_VConst(X, veclen, 0);
  fails += Test_N_VProd(X, Y, Z, veclen, 0);
  fails += Test_N_VDiv(X, Y, Z, veclen, 0);
  fails += Test_N_VScale(X, Z, veclen, 0);
  fails += Test_N_VAbs(X, Z, veclen, 0);
  fails += Test_N_VInv(X, Z, veclen, 0);
  fails += Test_N_VAddConst(X, Z, veclen, 0);
  fails += Test_N_VDotProd(X, Y, veclen, veclen, 0);
  fails += Test_N_VMaxNorm(X, veclen, 0);
  fails += Test_N_VWrmsNorm(X, Y, veclen, 0);
  fails += Test_N_VWrmsNormMask(X, Y, Z, veclen, veclen, 0);
  fails += Test_N_VMin(X, veclen, 0);
  fails += Test_N_VWL2Norm(X, Y, veclen, veclen, 0);
  fails += Test_N_VL1Norm(X, veclen, veclen, 0);
  fails += Test_N_VCompare(X, Z, veclen, 0);
  fails += Test_N_VInvTest(X, Z, veclen, 0);
  fails += Test_N_VConstrMask(X, Y, Z, veclen, 0);
  fails += Test_N_VMinQuotient(X, Y, veclen, 0);
  fails += Test_N_VCloneVectorArray(5, X, veclen, 0);
  fails += Test_N_VCloneEmptyVectorArray(5, X, 0);
  fails += Test_N_VCloneEmpty(X, 0);
  fails += Test_N_VClone(X, veclen, 0);

  /* Free vectors */
  N_VDestroy_Pthreads(W);
  N_VDestroy_Pthreads(X);
  N_VDestroy_Pthreads(Y);
  N_VDestroy_Pthreads(Z);

  /* Print result */
  if (fails) {
    printf("FAIL: NVector module failed %i tests \n \n", fails);
  } else {
    printf("SUCCESS: NVector module passed all tests \n \n");
  }

  return(0);
}