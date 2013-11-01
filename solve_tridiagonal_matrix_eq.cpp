#include <cmath>


void solve_tridiagonal_matrix_eq(int n, double *x, double *v)
{
    /* Function for solving the tridiagonal matrix equation by
     * the optimal method we introduced in the rapport.
     * Takes the arrays x and v by reference and the size variable
     * n as input.
     *
     * Important difference from algorithm in rapport:
     * In this function the variable f-tilde is called f.
     * */
    int i;

    double *d = new double[n];
    double *f = new double[n];
    double h;

    // Set step length:
    h = 1.0/(n+1);

    // Initialize the array d:
    for(i=0; i < n; i++){
        d[i] = 2;
    }

    // Construct the array x, which go from the value 0 to 1 with n+2 steps of distance h:
    for(i=0; i < n+2; i++){
        x[i] = h*i;
    }

    // Dirichlet boundary conditions:
    v[0] = 0;
    v[n+1] = 0;


    // Compute the array f, which contains the source term for our eqation:
    for(i=0; i < n; i++){
        f[i] = h*h*100*exp(-10*x[i+1]);
    }


    // Forward substitution:
    for(i=1; i < n; i++){
        d[i] -= 1/d[i-1];
        f[i] += f[i-1]/d[i-1];
    }

    // Backward substitution:
    // First step
    v[n] = f[n-1]/d[n-1];
    // Loop:
    for(i=n-1; i>0; i--){
        v[i] = (f[i-1] + v[i+1])/d[i-1];
    }
}
