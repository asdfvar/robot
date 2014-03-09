#!/usr/bin/python
import numpy as np
import math
import pylab as pl

N = 200
radius = 2.0
path_map = np.zeros(N)
R = np.linspace(-40,40,N) # positive goes to the left and negative goes to the right

POINTS = [np.array([-10, 5]), np.array([-10, 10]), np.array([-4, 30]), \
          np.array([6, 20]), np.array([8, -15])]

#POINTS = [np.array([-10, 5])]

THETA = np.arange(0, math.pi, 0.1)

for i,r in enumerate(R):
   path_map[i] = 2*math.pi*r
   for theta in THETA:
      I = np.array([-r, 0])
      y = I + r*np.array([math.cos(theta), math.sin(theta)])
      for point in POINTS:
         dist = np.linalg.norm(y-point)
         if dist <= radius:
            path_map[i] = r*theta

pl.plot(path_map)
pl.show()
