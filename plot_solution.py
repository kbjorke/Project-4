"""
Python script to plot the data we get from the output_files produced
by the program Project 3.

Pass the name of the output_file you want to plot as a 
commandline argumen.

Usage:
~$ python plot_system.pu output_EarthSunSystem.txt
"""
import sys
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Reads filename of output file from commandline
filename = sys.argv[-1]

input_file = open(filename, 'r')

# Starts with i = -2 because the two first lines
# of the outputfile contains only general information about the problem.
i = -1
for line in input_file:
    column = line.split()
    
    if i == -1:
        # Reads from first line in file:
        T = float(column[1])
        d = float(column[3])
        dt = float(column[5])
        dx = float(column[7])
        n = int(column[9])
        m = int(column[11])
        method = column[13]

        # Initialize arrays and matrices:

        position = np.linspace(0,d,n)
        time = np.linspace(0,T,m)

        t,x = np.meshgrid(time,position)

        solution = np.zeros([n, m])
        
    if ( i >= 0 ):
        # Reads values of the simulation
        solution[:,i] = [float(value) for value in column]

    i += 1

input_file.close()


# Find analytic solution: 
v = 0

epsilon = 1e-2

An = 1
n_ = 1
while np.abs(An) > epsilon:
    An = -2.0/(n_*np.pi*d)
    term = An*np.sin(n_*np.pi*x/d)*np.exp(-n_**2*np.pi**2*t/d**2) 
    v += term
    n_ += 1

u = v + 1 - x


t1 = 0.1
t2 = 0.8

i_t1 = int(round(t1/dt))
i_t2 = int(round(t2/dt))

resolution = 20.0

c_step = int(np.ceil(m/resolution))
r_step = int(np.ceil(n/resolution))

# Plot 3d plot of solution
fig1 = plt.figure(1)
ax1 = fig1.gca(projection='3d',
        xlabel='x-position',
        ylabel='time',
        zlabel='u(x,t)')

surf1 = ax1.plot_surface(x,t,solution, cmap=plt.cm.jet, 
        cstride=c_step, rstride=r_step, linewidth=0)
ax1.grid('on')
fig1.colorbar(surf1)

# Plot 3d plot of analytic solution (u)
fig2 = plt.figure(2)
ax2 = fig2.gca(projection='3d',
        xlabel='x-position',
        ylabel='time',
        zlabel='u(x,t)')

surf2 = ax2.plot_surface(x,t,u, cmap=plt.cm.jet, 
        cstride=c_step, rstride=r_step, linewidth=0)
ax2.grid('on')
fig2.colorbar(surf2)

# Plot 3d plot of error
fig3 = plt.figure(3)
ax3 = fig3.gca(projection='3d',
        xlabel='x-position',
        ylabel='time',
        zlabel='error')

surf3 = ax3.plot_surface(x,t,np.abs(u-solution), 
        cmap=plt.cm.jet, cstride=c_step, rstride=r_step, linewidth=0)
ax3.grid('on')
fig3.colorbar(surf3)

# Plot error at t1:
plt.figure(4)
plt.plot(position, np.abs(u[:,i_t1]-solution[:,i_t1])/
        (np.abs(u[:,i_t1])))
plt.xlabel('x-position')
plt.ylabel('relative error')

# Plot error at t2:
plt.figure(5)
plt.plot(position, np.abs(u[:,i_t2]-solution[:,i_t2])/
        (np.abs(u[:,i_t2])))
plt.xlabel('x-position')
plt.ylabel('relative error')

plt.show()

