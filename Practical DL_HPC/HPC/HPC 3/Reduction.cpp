#include <iostream>
#include <vector>
#include <omp.h>
#include <climits>

using namespace std;

int min_reduction(vector<int>& arr) {
  int min_value = INT_MAX;
  #pragma omp parallel for reduction(min: min_value)
  for (int i = 0; i < arr.size(); i++) {
    if (arr[i] < min_value) {
      min_value = arr[i];
    }
  }
  return min_value;
}

int max_reduction(vector<int>& arr) {
  int max_value = INT_MIN;
  #pragma omp parallel for reduction(max: max_value)
  for (int i = 0; i < arr.size(); i++) {
    if (arr[i] > max_value) {
      max_value = arr[i];
    }
  }
  return max_value;
}

int sum_reduction(vector<int>& arr) {
  int sum = 0;
   #pragma omp parallel for reduction(+: sum)
   for (int i = 0; i < arr.size(); i++) {
    sum += arr[i];
  }
  return sum;
}

double average_reduction(vector<int>& arr) {
  int sum = 0;
  #pragma omp parallel for reduction(+: sum)
  for (int i = 0; i < arr.size(); i++) {
    sum += arr[i];
  }
  return (double)sum / arr.size();
}

int main() {
  vector<int> arr;
  arr.push_back(5);
  arr.push_back(2);
  arr.push_back(9);
  arr.push_back(1);
  arr.push_back(7);
  arr.push_back(6);
  arr.push_back(8);
  arr.push_back(3);
  arr.push_back(4);

  int min_value = min_reduction(arr);
  int max_value = max_reduction(arr);
  int sum = sum_reduction(arr);
  double average = average_reduction(arr);

  cout << "Minimum value: " << min_value << endl;
  cout << "Maximum value: " << max_value << endl;
  cout << "Sum: " << sum << endl;
  cout << "Average: " << average << endl;
}

