import numpy as np
import struct

def load():
  e = np.loadtxt("kocke_e.txt")
  t = np.loadtxt("kocke_t.txt")
  return e, t

e, t = load()

def Viterbi(x):
    global t, e
    n = len(x)
    p_val = [0 for x in range(n+1)]
    n_val = [0 for x in range(n+1)]
    prev_0 = [0 for x in range(n+1)]
    prev_1 = [0 for x in range(n+1)]
    p_val[0] = 1
    n_val[0] = 1
    for i in range(n):
      num = ord(x[i]) - ord("0") - 1
      p_val[i+1] = max(p_val[i] * t[0][0], n_val[i] * t[1][0]) * e[0][num]
      n_val[i+1] = max(n_val[i] * t[1][1], p_val[i] * t[0][1]) * e[1][num]
      prev_0[i+1] = 0
      if p_val[i] * t[0][0] < n_val[i] * t[1][0]:
        prev_0[i+1] = 1
      prev_1[i+1] = 1
      if n_val[i] * t[1][1] < p_val[i] * t[0][1]:
        prev_1[i+1] = 0

    val = max(p_val[n], n_val[n])
 
    path = [0 for x in range(n+1)]
    path[n] = 0
    if p_val[n] < n_val[n]:
      path[n] = 1
    for i in range(n -1, 0, -1):
      if path[i+1]:
        path[i] = prev_1[i+1]
      else:
        path[i] = prev_0[i+1]
    
   # print(p_val)
    #print(n_val)    
    return val, path

def solve(x):
  val, path = Viterbi(x)
  print(val)
  print(path)

solve("123455666666123452")
solve("12345566123452")