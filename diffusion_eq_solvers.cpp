

void forward_euler(int n, int m, double alpha, double **u)
{
    int i, j;


    for( j = 1; j < m-1; j++ ){
        for( i = 1; i < m-1; i++ )
        {
            u[i][j] = alpha*u[i-1][j-1] + ( 1 - 2*alpha )*u[i][j-1] +
                    u[i+1][j-1];
        }
    }
}




void backward_euler(int n, int m, double alpha, double **u)
{

}
