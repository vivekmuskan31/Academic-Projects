import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm
import math
import os

# Image width and height; parameters for the plot
im_width, im_height = 250, 250
c = complex(-0.8,0.156) #fixed for whole iterations
zabs_max = 10  # max value allowed for z
nit_max = 500 # max iterations
xmin, xmax = -1.5, 1.5
xwidth = xmax - xmin
ymin, ymax = -1.5, 1.5
yheight = ymax - ymin

differentPowers=[2,3,4,5,10,20,50,100]
os.mkdir("Julia Trial for c = " +str(c.real)+'+i'+str(c.imag))
os.chdir("Julia Trial for c = " +str(c.real)+'+i'+str(c.imag))
for m in differentPowers:
    julia = np.zeros((im_width, im_height))
    for ix in range(im_width):
        for iy in range(im_height):
            nit = 0
            # Map pixel position to a point in the complex plane
            z = complex(ix / im_width * xwidth + xmin,
                        iy / im_height * yheight + ymin)
            # Do the iterations
            while abs(z) <= zabs_max and nit < nit_max:
                z = z**m + c
                nit += 1
            ratio = nit / nit_max
            julia[ix,iy] = ratio
    fig, ax = plt.subplots()
    plt.imshow(julia, interpolation='nearest', cmap=cm.hot)
    # Set the tick labels to the coordinates of z0 in the complex plane
    xLabels = np.linspace(xmin, xmax, xwidth / 0.5)
    # print(xLabels)
    ax.set_xticks([(x-xmin) / xwidth * im_width for x in xLabels])
    ax.set_xticklabels(['{:.1f}'.format(xtick) for xtick in xLabels])
    yLabels = np.linspace(ymin, ymax, yheight / 0.5)
    ax.set_yticks([(y-ymin) / yheight * im_height for y in yLabels])
    ax.set_yticklabels(['{:.1f}'.format(ytick) for ytick in yLabels])
    plt.title(str(c.real)+'+'+str(c.imag)+'j for n = '+str(m))
    plt.savefig('higherJulia '+str(m)+'_'+str(c.real)+'_'+str(c.imag)+'.png')

# fig, ax = plt.subplots()
# plt.imshow(julia, interpolation='nearest', cmap=cm.hot)
# # Set the tick labels to the coordinates of z0 in the complex plane
# xLabels = np.linspace(xmin, xmax, xwidth / 0.5)
# # print(xLabels)
# ax.set_xticks([(x-xmin) / xwidth * im_width for x in xLabels])
# ax.set_xticklabels(['{:.1f}'.format(xtick) for xtick in xLabels])
# yLabels = np.linspace(ymin, ymax, yheight / 0.5)
# ax.set_yticks([(y-ymin) / yheight * im_height for y in yLabels])
# ax.set_yticklabels(['{:.1f}'.format(ytick) for ytick in yLabels])
# plt.title(str(c.real)+'+'+str(c.imag)+'j')
# plt.savefig('higherJulia_'+str(c.real)+'_'+str(c.imag)+'.png')