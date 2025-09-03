#!/usr/bin/env python
import numpy as np
from scipy.sparse import csr_matrix
M = 4
N = 10
NNZ = 33
data = np.random.randint(1, 10, size=NNZ)  # NNZ nonzeros, in range of [0, 10)
rows = np.random.randint(0, M, size=NNZ)
cols = np.random.randint(0, N, size=NNZ)
A = csr_matrix((data, (rows, cols)), shape=(M, N)) # Create the CSR matrix
x = np.random.randint(1, 10, size=N) # Define a random vector x
z = A.dot(x) # z = Ax
print('enum {')
print(f'M   = {M},')
print(f'N   = {N},')
print(f'NNZ = {NNZ}')
print('};')

print('static int Gi[M+1] = {', ', '.join(map(str, A.indptr)), '};')  # Print A, x and z
print('static int Gj[NNZ] = {', ', '.join(map(str, A.indices)), '};')
print('static double Ga[NNZ] = {', ', '.join(map(str, A.data)), '};')
print('static double Xa[N] = {', ', '.join(map(str, x)), '};')
print('static double Za[M] = {', ', '.join(map(str, z)), '};')
print('static double Ya[M];')
