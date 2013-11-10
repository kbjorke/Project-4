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
    int i,j;
    double T, delta_t, delta_x;
    char *method;

    int n,m;
    double d, alpha;
    double **u;

    d = 1;

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

    n = ceil(d/delta_x);
    m = ceil(T/delta_t);

    alpha = delta_t/(delta_x*delta_x);

    cout << alpha << endl;

    // Problem definition, should be able to give as input, as function or
    // through input file.

    u = new double*[n];
    for( i = 0; i < n; i++ ){
        u[i] = new double[m];
    }

    for( i = 1; i < n-1; i++ )
    {
        u[i][0] = 0;

    }

    for( j = 0; j < m; j++ )
    {
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

