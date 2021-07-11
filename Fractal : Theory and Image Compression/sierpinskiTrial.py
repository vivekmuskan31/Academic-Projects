import math
import random
a=[0,0]
lent=3
b=[lent/2,lent*(math.sqrt(lent))/2]
c=[3,0]
p=[1,2]
list1=[]
for i in range(10000):
    list1.append(p)
    s=random.randint(0,2)
    if s==0:
        p=[(p[0]+a[0])/2,(p[1]+a[1])/2]
    elif s==1:
        p=[(p[0]+b[0])/2,(p[1]+b[1])/2]
    else:
        p=[(p[0]+c[0])/2,(p[1]+c[1])/2]
import matplotlib.pyplot as plt
xs=[x[0] for x in list1]
ys=[x[1] for x in list1]
plt.scatter(xs,ys,s=8)
plt.show()
plt.savefig('Sierpinski.png')
