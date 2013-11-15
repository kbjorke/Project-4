/* Program for Project 4, FYS3150.
 *
 * Solves the diffusion equation with a given set of variable for a
 * boundary conditions as described in report.
 *
 * Made by: Kristian Bjørke
 * */
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <cstring>

#include "diffusion_eq_solvers.h"
#include "output_data.h"

using namespace std;

int main(int argc, char *argv[])
{
    /* Main program.
     * Serves as the overlaying interface for the program, processes
     * the commandline input and runs the right functions.
     *
     * Takes input from command line:
     *
     *
     * Parameters:
     *
     *			-method :Set method to be used for the solution
     *					 (forward_euler, backward_euler, crank_nicolson)
     *
     * 			-T      :Set the end time of the solution.
     *
     *          -dx 		:Sets the spatial step of the solution.
     *
     *			-dt     :Sets the time step of the solution.
     *
     *
     * Output:	data_<method>_n<n>_T<T>_alpha<alpha>.txt
     *
     *
     * Use: $~ ./Project4 -T <end_time> -dt <time_step> -dx <spatial_step> -method <method>
     * */

    int i,j;
    double T, delta_t, delta_x;
    char *method;

    int n,m;
    double d, alpha;
    double **u;

    d = 1; // Defines max value for x-position.

    // Loop over commandline arguments to find parameters and options:
    for( i = 0; i < argc-1; i++ ){
        if( strcmp(argv[i], "-method") == 0 ){
            method = argv[i+1];
        }
        if( strcmp(argv[i], "-T") == 0 ){
            T = atof(argv[i+1]);
        }
        if( strcmp(argv[i], "-dx") == 0 ){
            delta_x = atof(argv[i+1]);
        }
        if( strcmp(argv[i], "-dt") == 0 ){
            delta_t = atof(argv[i+1]);
        }
    }

    // Calculate number of values along time and position axis
    n = ceil(d/delta_x) + 1;
    m = ceil(T/delta_t) + 1;


    alpha = delta_t/(delta_x*delta_x);


    u = new double*[n];
    for( i = 0; i < n; i++ ){
        u[i] = new double[m];
    }

    // Problem definition, should be able to give as input, as function or
    // through input file.

    for( i = 1; i < n-1; i++ )
    {
        // Initial conditions
        u[i][0] = 0;
    }

    for( j = 0; j < m; j++ )
    {
        // Boundary conditions
        u[0][j] = 1;
        u[n-1][j] = 0;
    }


    if( strcmp(method, "forward_euler") == 0 ){
        forward_euler(n, m, alpha, u);
    }
    if( strcmp(method, "backward_euler") == 0 ){
        backward_euler(n, m, alpha, u);
    }
    if( strcmp(method, "crank_nicolson") == 0 ){
        crank_nicolson(n, m, alpha, u);
    }

    output(n, m, T, d, delta_t, delta_x, alpha, method, u);
}

