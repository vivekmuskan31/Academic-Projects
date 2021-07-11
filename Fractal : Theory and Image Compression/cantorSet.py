import math
import random
a=0
b=1
p=0.5
list1=[]
for i in range(10000):
    s=random.randint(0,1)
    if s==0:
        p=p/3
    else:
        p=(2+p)/3
    list1.append(p)
    
import matplotlib.pyplot as plt
xs=list1
ys=[0 for x in list1]
plt.scatter(xs,ys,s=4)
plt.show()
plt.savefig('Cantor.png')
