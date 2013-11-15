"""
Python script to plot the error, either as a function of dt or
a function of dx for a chosed time t_error.

The script calls the Project4 program and reads the file to store
the value of the error for solution.

The script could use a interface, maybe commandline interface.

Usage:
~$ python plot_solution.py
"""

import sys
import os
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Start and stop value for the alpha values.
alpha_init = 0.5
alpha_end = 0.01

# Length of the error-array, how many aplha values do we want to solve for.
length = 4

# A chosen time to evaluete the error.
t_error = 0.8


T = 1.0
# Comment out dt if we want to find error as function of dt, and dx if dx.
#dt = 0.01
dx = 0.01

# Comment out m if we want to find error as function of dt, and m if dx.
#m = np.ceil(T/dt) + 1
n = np.ceil(1.0/dx) + 1

alpha_log_list = np.linspace(np.log10(alpha_init),np.log10(alpha_end),length)

log_error = np.zeros([3,length])

# Comment out methods containing 'forward_euler' if we want to run
# the script for alpha values larger then 0.5.
methods = ['forward_euler', 'backward_euler', 'crank_nicolson']
#methods = ['backward_euler', 'crank_nicolson']

# Loop to gather error values:
for p in range(len(alpha_log_list)):
    
    alpha = np.ceil(10**alpha_log_list[p]*10000)/10000
        
    # Comment out dx if we want to find error as function of dt, and dt if dx.
    #dx = np.sqrt(dt/alpha)
    dt = alpha*dx**2

    # Comment out n if we want to find error as function of dt, and m if dx.
    #n = np.ceil(1.0/dx) + 1
    m = np.ceil(T/dt) + 1

    position = np.linspace(0,1,n)
    time = np.linspace(0,T,m)

    t,x = np.meshgrid(time,position)

    solution = np.zeros([n, m])

    # Find index of chosen t-value for error evaluation
    i_t = int(round(t_error/dt))

    # Find analytic solution: 
    v = 0

    An = 1
    n_ = 1
    while n_ <= 20: 
        An = -2.0/(n_*np.pi)
        term = An*np.sin(n_*np.pi*x)*np.exp(-n_**2*np.pi**2*t) 
        v += term
        n_ += 1
        
    u = v + 1 - x

    for o in range(len(methods)):
        call = "./../Project4-build/Project4 -T %d -dt %f -dx %f -method %s" \
                % (T, dt, dx, methods[o])

        # Calls program Project4 with given variables:
        os.system(call)

        filename = "data_%s_n%d_T%d_alpha%05d.txt" %(methods[o], n, T*100, 
                round(alpha*10000))

        #Open file containing newly calculated values to be evaluated
        input_file = open(filename, 'r')

        # Starts with i = -1 because the two first lines
        # of the inpufile contains only general information about the problem.
        i = -1
        for line in input_file:
            column = line.split()
            
            if ( i >= 0 ):
               # Reads values of the simulation 
               solution[:,i] = [float(value) for value in column]


            i += 1

        input_file.close()

        # Store error:
        log_error[o][p] = np.max(np.log10(np.abs(u[:,i_t]-solution[:,i_t])))

        # Delete file:
        os.system("rm "+filename)

# Plot error:
fig = plt.figure(1)
ax1 = fig.add_subplot(111)
ax2 = ax1.twiny()

# Loop over all methods:
for o in range(len(methods)):
    ax1.plot(alpha_log_list, log_error[o,:])

ax1.set_xlim(np.log10(alpha_end), np.log10(alpha_init))
ax1.set_xlabel(r'$\log_10(\alpha)$')
ax1.set_ylabel(r'$\log_10(Error)$')
ax1.legend(methods, loc=2)

x_tick_loc = np.linspace(np.log10(alpha_init),np.log10(alpha_end),6)

# Comment out dx_list if we want to find error as function of dt, 
# and dt_list if dx.
#dx_list = np.sqrt(dt/(10**x_tick_loc))
#dx_list = [round(elem, 8) for elem in dx_list]
dt_list = (10**x_tick_loc)*(dx**2)
dt_list = [round(elem, 8) for elem in dt_list]

ax2.set_xticks(x_tick_loc)
ax2.set_xlim(np.log10(alpha_end), np.log10(alpha_init))
# Comment out dx_list if we want to find error as function of dt, 
# and dt_list if dx.
#ax2.set_xticklabels(dx_list)
#ax2.set_xlabel(r'$\Delta x$')
ax2.set_xticklabels(dt_list)
ax2.set_xlabel(r'$\Delta t$')

plt.show()
