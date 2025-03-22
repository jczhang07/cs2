// A sequential sparse matrix vector multiplication (SpMV, MatMult in PETSc)
#include <stdio.h>

// For simplicity, use global variables to store an M x N matrix A with NNZ nonzeros in the CSR format,
// and two vectors X, Z with Z = AX. The example was generated by the Python script crs.py
enum {
  M   = 32,
  N   = 36,
  NNZ = 50
};
static int    Gi[M + 1] = {0, 1, 1, 2, 6, 9, 10, 10, 11, 11, 13, 13, 13, 16, 17, 18, 18, 19, 20, 22, 23, 27, 28, 31, 32, 34, 37, 37, 41, 44, 44, 47, 49};
static int    Gj[NNZ]   = {25, 13, 1, 5, 7, 35, 18, 19, 31, 32, 21, 32, 33, 0, 8, 27, 16, 25, 3, 24, 17, 27, 13, 3, 28, 29, 30, 2, 23, 29, 31, 10, 8, 29, 1, 20, 22, 3, 8, 16, 19, 10, 14, 24, 2, 6, 15, 17, 34};
static double Ga[NNZ]   = {8, 3, 7, 5, 6, 7, 1, 9, 8, 9, 9, 9, 5, 1, 5, 8, 4, 4, 2, 11, 3, 8, 9, 7, 7, 4, 2, 2, 7, 6, 9, 3, 4, 2, 2, 9, 7, 4, 7, 8, 1, 8, 6, 1, 3, 3, 6, 6, 1};
static double Xa[N]     = {3, 2, 2, 7, 1, 5, 3, 3, 6, 6, 4, 8, 8, 4, 7, 8, 9, 7, 7, 6, 9, 5, 8, 5, 7, 5, 5, 5, 2, 4, 8, 1, 3, 6, 9, 8};
static double Za[M]     = {40, 0, 12, 113, 69, 27, 0, 45, 0, 57, 0, 0, 73, 36, 20, 0, 14, 77, 61, 36, 95, 4, 68, 12, 32, 141, 0, 148, 81, 0, 63, 51};
static double Ya[M];

// Petsc MATSEQAIJ matrix (aka compressed sparse row (CSR) storage)
typedef struct {
  int     m, n; // local row/column size
  int    *i;    // row pointer
  int    *j;    // column indices
  double *a;    // values
} Mat;

// Petsc VECSEQ vectors
typedef struct {
  int     n; // local size
  double *a; // values
} Vec;

int main(int argc, char **argv)
{
  Mat    A;
  Vec    x, y, z;
  double norm = 0;

  // Build A.  Because this is a sequential code, the local matrix takes all
  A.m = M;
  A.n = N;
  A.i = Gi;
  A.j = Gj;
  A.a = Ga;

  // Build x according to A's column size
  x.n = A.n;
  x.a = Xa;

  // Build y, z according to A's row size
  y.n = A.m;
  y.a = Ya;

  z.n = A.m;
  z.a = Za;

  // Compute y = Ax
  for (int i = 0; i < A.m; i++) {
    y.a[i] = 0.0;
    for (int j = A.i[i]; j < A.i[i + 1]; j++) y.a[i] += A.a[j] * x.a[A.j[j]];
  }

  // Compute the norm of ||y - z||
  for (int i = 0; i < A.m; i++) norm += (y.a[i] - z.a[i]) * (y.a[i] - z.a[i]);

  if (norm > 1e-6) {
    printf("Error in computing y = Ax, with norm = %f\n", norm);
    return 1;
  } else {
    printf("Succeeded in computing y = Ax\n");
    return 0;
  }
}
