#ifndef DIFFUSION_EQ_SOLVERS_H
#define DIFFUSION_EQ_SOLVERS_H


void forward_euler(int n, int m, double alpha, double **u);
void backward_euler(int n, int m, double alpha, double **u);
void crank_nicolson(int n, int m, double alpha, double **u);

#endif // DIFFUSION_EQ_SOLVERS_H
