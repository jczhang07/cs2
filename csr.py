#!/usr/bin/env python
import numpy as np
from scipy.sparse import csr_matrix
NR = 32
NC = 36
NNZ = 50
data = np.random.randint(1, 10, size=NNZ)  # NNZ nonzeros, in range of [0, 10)
rows = np.random.randint(0, NR, size=NNZ)
cols = np.random.randint(0, NC, size=NNZ)
A = csr_matrix((data, (rows, cols)), shape=(NR, NC)) # Create the CSR matrix
x = np.random.randint(1, 10, size=NC) # Define a random vector x
z = A.dot(x) # z = Ax
print("#define NR ", NR)
print("#define NC ", NC)
print("#define NNZ ", NNZ)
print("static int Gi[NR+1] = {", ", ".join(map(str, A.indptr)), "};")  # Print A, x and z
print("static int Gj[NNZ] = {", ", ".join(map(str, A.indices)), "};")
print("static double Ga[NNZ] = {", ", ".join(map(str, A.data)), "};")
print("static double Xa[NC] = {", ", ".join(map(str, x)), "};")
print("static double Za[NR] = {", ", ".join(map(str, z)), "};")
