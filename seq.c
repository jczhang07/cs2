// Sequential sparse matrix vector multiplication (MatMult)

#include <stdio.h>
#include <stdlib.h>

// Petsc MATSEQAIJ matrix (aka compressed sparse row (CSR) storage)
typedef struct {
  int     m, n; // local row/column size
  int    *i;    // row pointer
  int    *j;    // column indices
  double *a;    // values
} Mat;

// Petsc VECSEQ vector
typedef struct {
  int     n; // local size
  double *a; // values
} Vec;

// For simplicity, use global variables to store an NR x NC matrix A with NNZ nonzeros in the CSR format, and two vectors X, Z with Z = AX.
// The example was generated by the Python script crs.py
#define NR  32
#define NC  36
#define NNZ 50
static int    Gi[NR + 1] = {0, 1, 2, 2, 4, 5, 7, 9, 9, 12, 16, 19, 21, 23, 25, 26, 27, 28, 30, 30, 32, 34, 37, 37, 39, 40, 40, 41, 43, 46, 47, 48, 50};
static int    Gj[NNZ]    = {1, 22, 8, 15, 5, 0, 16, 15, 34, 3, 9, 27, 8, 14, 20, 31, 12, 13, 23, 5, 20, 0, 20, 13, 28, 21, 0, 0, 23, 33, 9, 23, 13, 24, 15, 30, 33, 1, 29, 11, 30, 4, 23, 5, 21, 30, 17, 5, 16, 34};
static double Ga[NNZ]    = {3, 8, 7, 3, 2, 1, 7, 3, 4, 4, 4, 7, 4, 5, 6, 4, 2, 6, 5, 7, 2, 5, 8, 9, 6, 8, 4, 4, 3, 7, 3, 2, 8, 5, 8, 8, 4, 9, 4, 1, 1, 4, 5, 9, 6, 3, 4, 5, 1, 5};
static double Xa[NC]     = {5, 2, 6, 1, 3, 7, 1, 7, 6, 5, 9, 6, 5, 4, 2, 6, 5, 5, 7, 3, 4, 8, 6, 4, 4, 1, 9, 7, 4, 9, 3, 3, 8, 9, 6, 1};
static double Za[NR]     = {6, 48, 0, 60, 14, 40, 42, 0, 73, 70, 54, 57, 57, 60, 64, 20, 20, 75, 0, 23, 52, 108, 0, 54, 6, 0, 3, 32, 120, 20, 35, 35};

int main(int argc, char **argv)
{
  Mat    A;
  Vec    x, y, z;
  double norm = 0;

  // Build A.  Because this is a sequential code, the local matrix takes all
  A.m = NR;
  A.n = NC;
  A.i = Gi;
  A.j = Gj;
  A.a = Ga;

  // Build x according to A's column size
  x.n = A.n;
  x.a = Xa;

  // Build y according to A's row size
  y.n = A.m;
  y.a = (double *)malloc(sizeof(double) * y.n);

  // Duplicate y to z, except the value
  z.n = y.n;
  z.a = Za;

  // Compute y = Ax
  for (int i = 0; i < A.m; i++) {
    y.a[i] = 0.0;
    for (int j = A.i[i]; j < A.i[i + 1]; j++) y.a[i] += A.a[j] * x.a[A.j[j]];
  }

  // Compare y with the answer z by computing the norm of ||y - z||
  for (int i = 0; i < A.m; i++) norm += (y.a[i] - z.a[i]) * (y.a[i] - z.a[i]);

  free(y.a);
  if (norm > 1e-6) {
    printf("Error in computing y = Ax, with norm = %f\n", norm);
    return 1;
  } else {
    printf("Succeeded in computing y = Ax\n");
    return 0;
  }
}
