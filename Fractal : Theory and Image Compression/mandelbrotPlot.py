import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm

MAX_ITER = 100

def mandelbrot(c):
    z = 0
    n = 0
    while abs(z) <= 2 and n < MAX_ITER:
        z = z*z + c
        n += 1
    return n

# Image size (pixels)
WIDTH = 500
HEIGHT = 500

# Plot window
RE_START = -2
RE_END = 1
IM_START = -2
IM_END = 2

mandle=np.zeros((WIDTH, HEIGHT))

for x in range(0, WIDTH):
    for y in range(0, HEIGHT):
        # Convert pixel coordinate to complex number
        c = complex(RE_START + (x / WIDTH) * (RE_END - RE_START),
                    IM_START + (y / HEIGHT) * (IM_END - IM_START))
        # Compute the number of iterations
        m = mandelbrot(c)
        # Plot the point
        mandle[y,x]=m/MAX_ITER
fig, ax = plt.subplots()
plt.imshow(mandle,interpolation='nearest', cmap=cm.hot)

xLabels = np.linspace(RE_START, RE_END, (RE_END-RE_START) / 0.5)
ax.set_xticks([(x-RE_START) / (RE_END-RE_START) * WIDTH for x in xLabels])
ax.set_xticklabels(['{:.1f}'.format(xtick) for xtick in xLabels])

yLabels = np.linspace(IM_START, IM_END, (IM_END-IM_START) / 0.5)
ax.set_yticks([(y-IM_START) / (IM_END-IM_START) * HEIGHT for y in yLabels])
ax.set_yticklabels(['{:.1f}'.format(ytick) for ytick in yLabels])

plt.title('Mandelbrot Set')
plt.savefig('mandlebrot.png')