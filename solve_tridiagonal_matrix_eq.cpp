#include <cmath>


void solve_tridiagonal_matrix_eq(int n, double *d, double *e,
                                          double *x, double *b)
{
    /* General function for solving a symetric tridiagonal matrix equation,
     * given on the form    Ax = b.
     * where A is a symmetric tridiagonal matrix with the the
     * vector-elements d on the diagonal and the vector-elements e on the
     * of-diagonal.
     *
     * Input:
     * 			- n : Dimensionality of the equation
     *
     * 			- d : A n-size vector containing the diagonal elemets of
     * 				  	matrix A.
     *
     *			- e : A (n-1)-size vector containing the of-diagonal elements
     *					of matrix A.
     *
     * 			- x : A reference to a n-size vector where the solution
     *					will be stored.
     *
     * 			- b : A n-size vector with known elements.
     * */

    int i;

    // Forward substitution:
    for( i = 1; i < n; i++ ){
        d[i] -= e[i-1]*e[i-1]/d[i-1];
        b[i] += b[i-1]*e[i-1]/d[i-1];
    }

    // Backward substitution:
    for( i = n-2; i > 0; i-- ){
        b[i] -= b[i-1]*e[i]/d[i+1];
    }

    // Find solution:
    for( i = 0; i < n; i++ ){
        x[i] = b[i]/d[i];
    }
}
