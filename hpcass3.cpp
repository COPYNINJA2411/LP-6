#include <iostream>
#include <omp.h>
#include <climits>
using namespace std;

int main() {
    const int n = 8;
    int arr[n] = {10, 20, 5, 30, 15, 25, 2, 40};

    int minVal = INT_MAX;
    int maxVal = INT_MIN;
    int sum = 0;

    // Parallel region with reduction
    #pragma omp parallel for reduction(min:minVal) reduction(max:maxVal) reduction(+:sum)
    for (int i = 0; i < n; ++i) {
        if (arr[i] < minVal) minVal = arr[i];
        if (arr[i] > maxVal) maxVal = arr[i];
        sum += arr[i];
    }

    double average = (double)sum / n;

    // Output
    cout << "Minimum: " << minVal << endl;
    cout << "Maximum: " << maxVal << endl;
    cout << "Sum: " << sum << endl;
    cout << "Average: " << average << endl;

    return 0;
}

