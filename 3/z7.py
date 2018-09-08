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
  if x == "_" or y == "_":
    return -8
  return bm[acids.index(x)][acids.index(y)]
 
## score matrix
def create_sm(x, y, n, m):
    global acids
    global bm
    sm=[]
    tmp=[]
    for i in range(m+1):
        tmp.append(0)
    for i in range(n+1):
        sm.append(tmp[:])
        
    for i in range(n+1):
        sm[i][0]=-8*i
    for i in range(m+1):
        sm[0][i]=-8*i
    
    for i in range(1, n+1):
        for j in range(1, m+1):
            tmp=[]
            tmp.append(sm[i-1][j]-8)
            tmp.append(sm[i][j-1]-8)
            bb = score(y[i-1], x[j-1])
            tmp.append(sm[i-1][j-1] + bb)
            tmp.sort()
            sm[i][j]=tmp[-1]
    return sm
  
# Statistical sum matrix
def create_ss(x, y):
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

##  reconstruct path from score matrix
##  yields the optimal sequence alignment
def traceback(i, j, x, y, sm):
    # end
    if i == 0 and j == 0:
        return "", ""
    # left end
    if j == 0:
        u, d = traceback(i - 1, j, x, y, sm)
        return u + '_', d + y[i-1]
    # up end
    if i == 0:
        u, d = traceback(i, j - 1, x, y, sm)
        return u + x[j-1], d + '_'

    s1 = sm[i-1][j] - 8
    s2 = sm[i][j-1] - 8
    #print(i, j)
    s3 = sm[i-1][j-1]
    s3 = s3 + score(y[i-1], x[j-1])
    #   up
    if s1 >= s2 and s1 >= s3:
        u, d = traceback(i - 1, j, x, y, sm)
        return u + '_', d + y[i-1]

    #   left
    if s2 >= s1 and s2 >= s3:
        u, d = traceback(i, j - 1, x, y, sm)
        return u + x[j-1], d + '_'

    #  left and up
    u, d = traceback(i-1, j-1, x, y, sm)
    return u + x[j-1], d + y[i-1]

def align_prob(l, up, down, total_ss):  
  l_id = up.index(l)
  up_l = up[:l_id]
  down_l = down[:l_id]
  l_up = up[l_id + 1 :]
  l_down = down[l_id + 1 :]
  ss_l = create_ss(down_l, up_l)
  l_ss = create_ss(l_down, l_up)
  
  score_l = ss_l[-1][-1]
  if len(up_l) == 0:
    score_l = 1
  l_score = l_ss[-1][-1]
  if (len(l_up)) == 0:
    l_score = 1
    
  prob = score_l * np.exp(score(l, l)) * l_score
  prob = prob / total_ss
  return prob
  

def solve(x, y):
  stat_sum = create_ss(x, y)
  print(stat_sum)
  np.set_printoptions(formatter={'float': '{:10.4e}'.format})
  n, m = len(x), len(y)
  score_mat = create_sm(x, y, m, n)
  up, down = traceback(m, n, x, y, score_mat)
  print(up)
  print(down)
  print(np.exp(score_mat[-1][-1]) / stat_sum[-1][-1])

  prob = align_prob("P", up, down, stat_sum[-1][-1])
  print(prob)
 # ss[prije pp] * score[pp] * ss[poslije pp]

#solve("HPEW", "PW")
#solve("PW", "AHPAWA")
solve("P", "P")
