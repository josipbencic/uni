import numpy as np
from numpy import linalg as la

def solve():
  pam1 = np.loadtxt("PAM1.txt")
  np.linalg.matrix_power(pam1, 1000)
  print(pam1)

solve()