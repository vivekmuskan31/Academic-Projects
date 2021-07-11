import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm
import math

# Image width and height; parameters for the plot
im_width, im_height = 500, 500
c = complex((1-math.sqrt(5))/2,0) #fixed for whole iterations
zabs_max = 10  # max value allowed for z
nit_max = 1000 # max iterations
xmin, xmax = -1.5, 1.5
xwidth = xmax - xmin
ymin, ymax = -1.5, 1.5
yheight = ymax - ymin

julia = np.zeros((im_width, im_height))
for ix in range(im_width):
    for iy in range(im_height):
        nit = 0
        # Map pixel position to a point in the complex plane
        z = complex(ix / im_width * xwidth + xmin,
                    iy / im_height * yheight + ymin)
        # Do the iterations
        while abs(z) <= zabs_max and nit < nit_max:
            z = z**2 + c
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
plt.title(str(c.real)+'+'+str(c.imag)+'j')
plt.savefig('julia_'+str(c.real)+'_'+str(c.imag)+'.png')