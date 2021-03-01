#include <iostream>
#include <omp.h>

using namespace std;

int main()
{
    int i;
    int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
    int b[10] = { 1,2,3,4,5,6,7,8,9,10 };
    int result[10];

    omp_set_num_threads(4);

    for (int i = 0; i < 10; i++) {
        result[i] = a[i] + b[i];
    }

    for (int i = 0; i < 10; i++) {
        cout << result[i] << ' ';
    }
    cout << endl;

    #pragma omp parallel private(i) num_threads(3)
    {
        /*#pragma omp for private(i) schedule(static, 1)
        for (int i = 0; i < 10; i++) {
            cout << omp_get_thread_num() << " - " << i << endl;
            result[i] = a[i] + b[i];
        }
        cout << "end for1 for thread " << omp_get_thread_num() << endl;

        #pragma omp for nowait
        for (int i = 0; i < 10; i++) {
            cout << result[i] << ' ';
        }
        cout << endl;
        cout << "end for2 for thread " << omp_get_thread_num() << endl;*/
        #pragma omp sections
        {
            #pragma omp section
            {

            }
            #pragma omp section
            {

            }
            #pragma omp section
            {

            }
        }
    }



}