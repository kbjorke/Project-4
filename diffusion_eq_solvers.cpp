#include "solve_tridiagonal_matrix_eq.h"

/* Function for solving diffusion equation using the
 * explicit Forward Euler method.
 *
 * Input:
 *
 * 			- n : amount of points for position
 *
 * 			- m : amount of points for time
 *
 *			- alpha : contains time step (dt) and spatial
 *					  step (dx) as dt/dx^2. Needed for
 *					  solutions.
 *
 *			- **u : n x m - matrix which must contain
 *					boundary and initial conditions, rest
 *					of matrix will be filled as problem
 *					is solved.
 * */

void forward_euler(int n, int m, double alpha, double **u)
{
    static int i, j;

    for( j = 1; j < m; j++ ){
        for( i = 1; i < n-1; i++ )
        {
            u[i][j] = alpha*u[i-1][j-1] + ( 1 - 2*alpha )*u[i][j-1] +
                    alpha*u[i+1][j-1];
        }
    }
}



/* Function for solving diffusion equation using the
 * implicit Backward Euler method.
 *
 * Input:
 *
 * 			- n : amount of points for position
 *
 * 			- m : amount of points for time
 *
 *			- alpha : contains time step (dt) and spatial
 *					  step (dx) as dt/dx^2. Needed for
 *					  solutions.
 *
 *			- **u : n x m - matrix which must contain
 *					boundary and initial conditions, rest
 *					of matrix will be filled as problem
 *					is solved.
 * */

void backward_euler(int n, int m, double alpha, double **u)
{
    static int i, j;
    static double d;
    double *A_d, *A_e, *V, *V_prev;

    A_d = new double[n-2];
    A_e = new double[n-3];
    V = new double[n-2];
    V_prev = new double[n-2];


    // Constructing tridiagonal matrix:
    d = 1 + 2*alpha;

    A_d[0] = d;
    for( i = 0; i < n-3; i++ )
    {
        A_d[i+1] = d;
        A_e[i] = -alpha;
    }

    // Solving problem
    for( j = 1; j < m; j++ ){
        for( i = 1; i < n-1; i++ )
        {
            V_prev[i-1] = u[i][j-1];
        }

        // Adding boundary conditions, since they are not
        // included in the tridiagonal matrix:
        V_prev[0] += alpha*u[0][j];
        V_prev[n-3] += alpha*u[n-1][j];

        solve_tridiagonal_matrix_eq(n-2, A_d, A_e, V, V_prev);

        for( i = 1; i < n-1; i++ )
        {
            u[i][j] = V[i-1];
        }
    }
}

/* Function for solving diffusion equation using the
 * implicit Crank-Nicolson method.
 *
 * Input:
 *
 * 			- n : amount of points for position
 *
 * 			- m : amount of points for time
 *
 *			- alpha : contains time step (dt) and spatial
 *					  step (dx) as dt/dx^2. Needed for
 *					  solutions.
 *
 *			- **u : n x m - matrix which must contain
 *					boundary and initial conditions, rest
 *					of matrix will be filled as problem
 *					is solved.
 * */

void crank_nicolson(int n, int m, double alpha, double **u)
{
    static int i, j;
    static double d;
    double *A_d, *A_e, *V, *V_prev;

    A_d = new double[n-2];
    A_e = new double[n-3];
    V = new double[n-2];
    V_prev = new double[n-2];


    // Constructing tridiagonal matrix:
    d =  2 + 2*alpha;

    A_d[0] = d;
    for( i = 0; i < n-3; i++ )
    {
        A_d[i+1] = d;
        A_e[i] = -alpha;
    }

    // Solving problem:
    for( j = 1; j < m; j++ ){
        for( i = 1; i < n-1; i++ )
        {
            // Half Forward Euler step:
            V_prev[i-1] = alpha*u[i-1][j-1] + ( 2 - 2*alpha )*u[i][j-1] +
                        alpha*u[i+1][j-1];
        }

        // Adding boundary conditions, since they are not
        // included in the tridiagonal matrix:
        V_prev[0] += alpha*u[0][j];
        V_prev[n-3] += alpha*u[n-1][j];

        solve_tridiagonal_matrix_eq(n-2, A_d, A_e, V, V_prev);

        for( i = 1; i < n-1; i++ )
        {
            u[i][j] = V[i-1];
        }
    }
}
