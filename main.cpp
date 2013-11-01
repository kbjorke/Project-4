#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int n,m;
    int i,j;
    double d;

    double u[n][m];
    double v[n][m];

    for( i = 1; i < n-1; i++ )
    {
        u[i][0] = 0;

    }

    for( j = 0; j < m; j++ )
    {
        u[0][j] = 1;
        u[n-1][j] = 0;
    }


}

