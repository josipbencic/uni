
f1=open("acids.txt", "r") ## reading acids
ak=f1.readline()
f1.close()

bm=[] ## reading matrix
f1=open("blosum50.txt", "r")
for i in range(20):
    line=f1.readline()
    vc=line.split()
    bm.append(vc[:])
for i in range(20): ## integer matrix
    for j in range(20):
        bm[i][j]=int(bm[i][j])

x='HPEW'
y='PWAA'
m=len(x)
n=len(y)

sm=[] ## score matrix
tmp=[]
for i in range(m+1):
    tmp.append(0)
for i in range(n+1):
    sm.append(tmp[:])

## rubni uvjeti
for i in range(n+1):
    sm[i][0]=-8*i
for i in range(m+1):
    sm[0][i]=-8*i

## rekurzija
for i in range(1,n+1):
    for j in range(1,m+1):
        tmp=[]
        tmp.append(sm[i-1][j]-8)
        tmp.append(sm[i][j-1]-8)
        bb=bm[ak.index(y[i-1])][ak.index(x[j-1])]
        tmp.append(sm[i-1][j-1]+bb)
        tmp.sort()
        sm[i][j]=tmp[2]


up = ""
down = ""

def traceback(i, j):
    global up
    global down
    global x
    global y

    print(i, j)
    # kraj
    if i == 0 and j == 0:
        return
    # lijevi rub
    if j == 0:
        up = up + '_'
        down = down + y[i-1]
        return traceback(i - 1, j)

    # gornji rub
    if i == 0:
        up = up + x[j-1]
        down = down +  '_'
        return traceback(i, j - 1)

    s1 = sm[i-1][j] - 8
    s2 = sm[i][j-1] - 8
    s3 = sm[i-1][j-1] + bm[i][j]

    if s1 >= s2 and s1 >= s3:
        up = up + '_'
        down = down + y[i-1]
        return traceback(i - 1, j)

    if s2 >= s1 and s2 >= s3:
        up = up + x[j-1]
        down = down + '_'
        return traceback(i, j - 1)
    
    up = up + x[j-1]
    down = down + y[i-1]
    return traceback(i-1, j-1)

traceback(n, m)
print(up[::-1])
print(down[::-1])
print(sm)