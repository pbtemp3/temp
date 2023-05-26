#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

void parallel_bubble_sort(int arr[], int n, int num_threads) {
    int i, j;
    for (i = 0; i < n-1; i++) {
        #pragma omp parallel for num_threads(num_threads) default(none) shared(arr, n, i) private(j)
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

int main() {
    srand(time(nullptr));

    int n = 100000;
    int arr[n];
    for (int i = 0; i < n; i++) {
        arr[i] = rand();
    }

    int num_threads = 12; // set number of threads
    omp_set_num_threads(num_threads);

    // measure time for sequential bubble sort
    clock_t start_seq = clock();
    bubble_sort(arr, n);
    clock_t end_seq = clock();
    double time_seq = double(end_seq - start_seq) / CLOCKS_PER_SEC;
    cout << "Sequential bubble sort took " << time_seq << " seconds." << endl;

    // measure time for parallel bubble sort
    clock_t start_par = clock();
    parallel_bubble_sort(arr, n, num_threads);
    clock_t end_par = clock();
    double time_par = double(end_par - start_par) / CLOCKS_PER_SEC;
    cout << "Parallel bubble sort took " << time_par << " seconds." << endl;

    return 0;
}

