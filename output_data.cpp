#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;

/* Function that writes solution to file.
 *
 * Input:
 *
 *			- n: amount of points to describe position
 *
 *			- m: amount of point to describe time
 *
 *			- T: final time of solution
 *
 *			- d: largest positions
 *
 *			- delta_t: time step
 *
 *			- delta_x: spatial step
 *
 *			- alpha: alpha value for solution, given by delta_t/delta_x^2
 *
 *			- *method: name of methods used for solution
 *
 * 			- **u: n x m - matrix containing solution
 *
 *
 * Output:
 *
 *			- Filename: data_<method>_n<n>_T<T>_alpha<alpha>.txt
 *
 * */
void output(int n, int m, double T, double d,
            double delta_t, double delta_x, double alpha,
            char *method, double **u)
{
    int i, j;

    string output_file;
    ostringstream oss;

    // Generate filename for output file
    oss << "data_" << method  << "_n" <<
           n << "_T" <<
           setw(3) << setfill('0') << int(T*100) << "_alpha" <<
           setw(5) << setfill('0') << int(round(alpha*10000)) <<
           ".txt" << '\0' << endl;

    output_file = oss.str();

    fstream myfile;
    myfile.open(output_file.c_str(), ios::out);

    // Write out first line in output file, general data about solution
    myfile << "T: " << T << '\t' <<
              "d: " << d << '\t' <<
              "dt: " << delta_t << '\t' <<
              "dx: " << delta_x << '\t' <<
              "n: " << n << '\t' <<
              "m: " << m << '\t' <<
              "alpha: " << alpha << '\t' <<
              "method: " << method << '\t' << endl;

    // Writes out solution
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
