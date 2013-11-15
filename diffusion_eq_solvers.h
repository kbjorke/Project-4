#ifndef DIFFUSION_EQ_SOLVERS_H
#define DIFFUSION_EQ_SOLVERS_H

/* Functions for solving diffusion equation.
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

void forward_euler(int n, int m, double alpha, double **u);
void backward_euler(int n, int m, double alpha, double **u);
void crank_nicolson(int n, int m, double alpha, double **u);

#endif // DIFFUSION_EQ_SOLVERS_H
