import numpy as np
from numpy import linalg as la

def solve():
  raw = np.loadtxt("PAM1.txt", np.float64)
  pam1 = np.multiply(1/10000, raw)
  #print(pam1)
  a =  la.matrix_power(pam1, 1000)
  
  for i in range(0, len(a)):
    for j in range(0, len(a[i])):
      print(a[i][j])
    print("")

solve()