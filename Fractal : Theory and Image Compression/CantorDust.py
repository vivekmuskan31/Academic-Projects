import math
import random
a=[0,0]
lent=3
b=[1,0]
c=[0,1]
d=[1,1]
p=[0.5,0.5]
list1=[]
for i in range(10000):
    list1.append(p)
    s=random.randint(0,3)
    if s==0:
        p=[(p[0])/3,(p[1])/3]
    elif s==1:
        p=[(p[0]+2)/3,(p[1])/3]
    elif s==2:
        p=[(p[0]+2)/3,(p[1]+2)/3]
    else:
        p=[(p[0])/3,(p[1]+2)/3]
    
    
import matplotlib.pyplot as plt
xs=[x[0] for x in list1]
ys=[x[1] for x in list1]
plt.scatter(xs,ys,s=1)
plt.show()
plt.savefig('cantorDust.png')
