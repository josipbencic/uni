## score matrix
def compute_sm(x, y, n, m, bm, acids):
    sm=[]
    tmp=[]
    for i in range(m+1):
        tmp.append(0)
    for i in range(n+1):
        sm.append(tmp[:])

    ## edge
    for i in range(n+1):
        sm[i][0] = 0
    for i in range(m+1):
        sm[0][i] = 0

    ## recursion
    for i in range(1,n+1):
        for j in range(1,m+1):
            tmp=[]
            tmp.append(sm[i-1][j] - 8)
            tmp.append(sm[i][j-1] - 8)
            bb = bm[acids.index(y[i-1])][acids.index(x[j-1])]
            tmp.append(sm[i-1][j-1] + bb)
            tmp.append(0)
            tmp.sort()
            sm[i][j] = tmp[-1]
    return sm

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


##  reconstruct path from score matrix
##  yields the optimal sequence alignment
def traceback(i, j, x, y, sm, bm, acids):
    # end
    if (i == 0 and j == 0) or sm[i][j] == 0:
        return "", ""
    # left end
    if j == 0:
        u, d = traceback(i - 1, j, x, y, sm, bm, acids)
        return u + '_', d + y[i-1]
    # up end
    if i == 0:
        u, d = traceback(i, j - 1, x, y, sm, bm, acids)
        return u + x[j-1], d + '_'

    s1 = sm[i-1][j] - 8
    s2 = sm[i][j-1] - 8
    s3 = sm[i-1][j-1] + bm[acids.index(y[i-1])][acids.index(x[j-1])]
    
    #   up
    if s1 >= s2 and s1 >= s3:
        u, d = traceback(i - 1, j, x, y, sm, bm, acids)
        return u + '_', d + y[i-1]

    #   left
    if s2 >= s1 and s2 >= s3:
        u, d = traceback(i, j - 1, x, y, sm, bm, acids)
        return u + x[j-1], d + '_'

    #  left and up
    u, d = traceback(i-1, j-1, x, y, sm, bm, acids)
    return u + x[j-1], d + y[i-1]

def solve():
    acids, bm = load_acids_blosum()
    
    # test case
    x='PEW'
    y='GALAPAWALA'
    m, n = len(x), len(y)
    sm = compute_sm(x, y, n, m, bm, acids)

    
    si, sj, max_val = 0, 0, sm[0][0]
    for i in range(0, len(sm)):
      for j in range(0, len(sm[i])):
        if sm[i][j] > sm[si][sj]:
          max_val = sm[si][sj]
          si, sj = i, j
    print(si, sj, max_val)
    u, d = traceback(si, sj, x, y, sm, bm, acids)
    print(u)
    print(d)
    for z in sm:
      print(z)

solve()