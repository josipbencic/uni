import numpy as np

## load acids and blosum50 matrix from the disk
def load_acids_blosum():
    ## reading acids
    f1=open("acids.txt", "r")
    acids =f1.readline()
    f1.close()

    ## reading matrix
    bm=[]
    f1=open("blosum50.txt", "r")
    for i in range(20):
        line=f1.readline()
        vc=line.split()
        bm.append(vc[:])
    
    ## integer matrix
    for i in range(20):
        for j in range(20):
            bm[i][j]=int(bm[i][j])

    return acids, bm


acids, bm = load_acids_blosum()

def score(x, y):
  global acids
  global bm
  return bm[acids.index(x)][acids.index(y)]

def create_SS(x, y):
  m, n = len(x), len(y)
  SS = np.zeros(shape=(n+1, m+1))
  for j in range(1, m + 1):
    SS[0][j] = np.exp(-8 * j)
  for i in range(1, n + 1):
    SS[i][0] = np.exp(-8 * i)

  e_8 = np.exp(-8)
  for i in range(1, n + 1):
    for j in range(1, m + 1):
      SS[i][j] = SS[i][j-1] * e_8 + SS[i-1][j] * e_8
      SS[i][j] = SS[i][j] + SS[i-1][j-1] * np.exp(score(x[j-1], y[i-1]))
  return SS
  
def solve(x, y):
  ss = create_SS(x, y)
  np.set_printoptions(formatter={'float': '{:10.4e}'.format})
  print(ss[-1][-1])
 
solve("HPEW", "PW")