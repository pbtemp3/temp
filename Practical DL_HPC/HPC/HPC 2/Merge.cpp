#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = arr[m + 1+ j];
    }
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(int arr[], int l, int r) {
    if (l < r) {
        int m = l+(r-l)/2;
        merge_sort(arr, l, m);
        merge_sort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

void parallel_merge_sort(int arr[], int l, int r, int num_threads) {
    if (l < r) {
        int m = l+(r-l)/2;
        #pragma omp parallel sections num_threads(2)
        {
            #pragma omp section
            {
                parallel_merge_sort(arr, l, m, num_threads/2);
            }
            #pragma omp section
            {
                parallel_merge_sort(arr, m+1, r, num_threads/2);
            }
        }
        merge(arr, l, m, r);
    }
}

int main() {
    srand(time(nullptr));

    int n = 1000000;
    int arr[n];
    for (int i = 0; i < n; i++) {
        arr[i] = rand();
    }

    int num_threads = 12; // set number of threads
    omp_set_num_threads(num_threads);

    // measure time for sequential merge sort
    clock_t start_seq = clock();
    merge_sort(arr, 0, n-1);
    clock_t end_seq = clock();
    double time_seq = double(end_seq - start_seq) / CLOCKS_PER_SEC;
    cout << "Sequential merge sort took " << time_seq << " seconds." << endl;

    // measure time for parallel merge sort
    clock_t start_par = clock();
    parallel_merge_sort(arr, 0, n-1, num_threads);
    clock_t end_par = clock();
    double time_par = double(end_par - start_par) / CLOCKS_PER_SEC;
    cout << "Parallel merge sort took " << time_par << " seconds." << endl;

    return 0;
}

