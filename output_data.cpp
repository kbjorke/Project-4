#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

void output(int n, int m, double T, double d,
            double delta_t, double delta_x, double alpha,
            char *method, double **u)
{
    int i, j;

    string output_file;
    ostringstream oss;

    oss << "data_" << method  << "_n" <<
           n << "_T" <<
           setw(3) << setfill('0') << int(T*100) << "_alpha" <<
           setw(5) << setfill('0') << int(alpha*10000) <<
           ".txt" << '\0' << endl;

    output_file = oss.str();

    fstream myfile;
    myfile.open(output_file.c_str(), ios::out);

    myfile << "T: " << T << '\t' <<
              "d: " << d << '\t' <<
              "dt: " << delta_t << '\t' <<
              "dx: " << delta_x << '\t' <<
              "n: " << n << '\t' <<
              "m: " << m << '\t' <<
              "alpha: " << alpha << '\t' <<
              "method: " << method << '\t' << endl;

    myfile.precision(10);
    myfile << scientific;
    for( j = 0; j < m; j++ ){
        for( i = 0; i < n; i++ )
        {
            myfile << u[i][j] << "   ";
        }
        myfile << endl;
    }

    myfile.close();
}
