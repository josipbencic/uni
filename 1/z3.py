import random
 
def create_array(a, b):
  vec = []
  for i in a:
    vec.append(0)
  for i in b:
    vec.append(1)
  random.shuffle(vec)
   #vec = [1, 0, 0, 1, 0, 0]
  print(vec)
  
  x, y = [], []
  last, ait, bit, i = 1, 0, 0, 0
  for z in vec:
    if z == last:
      if z == 0:
        x.append(a[ait])
        y.append("_")
        ait = ait + 1
      else:
        x.append("_")
        y.append(b[bit])
        bit = bit + 1
    else:
      if z:
        y.append(b[bit])
        bit = bit + 1
      else:
        x.append(a[ait])
        ait = ait + 1
    last = z
    
  if len(x) < len(y):
    x.append("_")
  elif len(y) < len(x):
    y.append("_")
  return "".join(x), "".join(y)
  
def solve():
  a = "HPEW"
  b = "PW"

  for i in range(1, 2):
    x, y = create_array(a, b)
    print(x)
    print(y)

solve()