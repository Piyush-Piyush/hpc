#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

#define MAX_SIZE 100 // Adjust this as needed

vector<long long> fibonacci(MAX_SIZE); // Shared vector to store Fibonacci series
int count = 0;                        // Shared counter to track generated numbers
int limit;                            // Limit for the Fibonacci series

int main() {
    cout << "Enter the limit for the Fibonacci series: ";
    cin >> limit;

    if (limit <= 0 || limit > MAX_SIZE) {
        cout << "Please enter a positive number less than or equal to " << MAX_SIZE << ".\n";
        return 1;
    }

    #pragma omp parallel sections
    {
        // Section for generating Fibonacci numbers
        #pragma omp section
        {
            fibonacci[0] = 0;
            if (limit > 1) {
                fibonacci[1] = 1;
            }

            for (int i = 2; i < limit; ++i) {
                fibonacci[i] = fibonacci[i - 1] + fibonacci[i - 2];
            }

            // Update count to indicate all numbers are generated
            #pragma omp critical
            {
                count = limit;
            }
        }

        // Section for printing Fibonacci numbers
        #pragma omp section
        {
            int printed = 0;
            while (printed < limit) {
                #pragma omp critical
                {
                    if (printed < count) {
                        cout << fibonacci[printed] << " ";
                        ++printed;
                    }
                }
            }
            cout << endl;
        }
    }

    return 0;
}
