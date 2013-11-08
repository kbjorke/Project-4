#include "solve_tridiagonal_matrix_eq.h"


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




void backward_euler(int n, int m, double alpha, double **u)
{
    static int i, j;
    static double d;
    double *A_d, *A_e, *V, *V_prev;

    A_d = new double[n-2];
    A_e = new double[n-3];
    V = new double[n-2];
    V_prev = new double[n-2];

    d = 1 + 2*alpha;

    A_d[0] = d;
    for( i = 0; i < n-3; i++ )
    {
        A_d[i+1] = d;
        A_e[i] = -alpha;
    }

    for( j = 1; j < m; j++ ){
        for( i = 1; i < n-1; i++ )
        {
            V_prev[i-1] = u[i][j-1];
        }

        V_prev[0] += alpha*u[0][j-1];
        V_prev[n-3] += alpha*u[n-1][j-1];

        solve_tridiagonal_matrix_eq(n-2, A_d, A_e, V, V_prev);

        for( i = 1; i < n-1; i++ )
        {
            u[i][j] = V[i-1];
        }
    }
}


void crank_nicolson(int n, int m, double alpha, double **u)
{
    static int i, j;
    static double d;
    double *A_d, *A_e, *V, *V_prev;

    A_d = new double[n-2];
    A_e = new double[n-3];
    V = new double[n-2];
    V_prev = new double[n-2];

    d = 2 + 2*alpha;

    A_d[0] = d;
    for( i = 0; i < n-3; i++ )
    {
        A_d[i+1] = d;
        A_e[i] = -alpha;
    }

    for( j = 1; j < m; j++ ){
        for( i = 1; i < n-1; i++ )
        {
            V_prev[i-1] = alpha*u[i-1][j-1] + ( 2 - 2*alpha )*u[i][j-1] +
                        alpha*u[i+1][j-1];
        }
        V_prev[0] += alpha*u[0][j-1];
        V_prev[n-3] += alpha*u[n-1][j-1];

        solve_tridiagonal_matrix_eq(n-2, A_d, A_e, V, V_prev);

        for( i = 1; i < n-1; i++ )
        {
            u[i][j] = V[i-1];
        }
    }
}
