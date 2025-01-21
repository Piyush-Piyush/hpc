#include <iostream>
#include <omp.h>
#include <vector>
using namespace std;

int main() {
    int n;
    cout << "Enter matrix size: ";
    cin >> n;

    vector<vector<int>> A(n, vector<int>(n));
    vector<int>B(n);
    vector<int> x(n), y(n);

    cout << "Enter matrix A :\n";
    for(auto &row : A) {
        for(int &a : row) {
            cin >> a;
        }
    }

    cout << "Enter vector B: \n";
    for(int &bi : B) {
        cin >> bi;
    }

    // serial execution
    double start_serial = omp_get_wtime();
    for(int i = 0; i < n; i++) {
        for(int j = 0; j<n; j++) {
            x[i] += A[i][j] * B[j];
        }
    }
    double end_serial = omp_get_wtime();


    // parallel execution 

    double start_parallel = omp_get_wtime();
    #pragma omp parallel for
    for(int i = 0; i < n; i++) {
        for(int j = 0; j<n; j++) {
            y[i] += A[i][j] * B[j];
        }
    }
    double end_parallel = omp_get_wtime();


    cout<<"Result for serial execution: "<<endl;
    for(int i = 0; i<n; i++) {
        cout<<x[i]<<" ";
    }
    cout<<endl;
    cout<<"Serial execution time : " << end_serial-start_serial<<endl;

    cout<<"Result for parallel execution: "<<endl;
    for(int i = 0; i<n; i++) {
        cout<<y[i]<<" ";
    }
    cout<<endl;
    cout<<"Parallel execution time : " << end_parallel-start_parallel<<endl;


    return 0;

}