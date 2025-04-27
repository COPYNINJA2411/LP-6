#include <iostream>
#include <vector>
#include <omp.h>
#include <chrono>
#include <cstdlib> // for rand()
using namespace std;
using namespace std::chrono;

// Threshold to switch to sequential sort in parallel merge sort
const int MERGE_SORT_THRESHOLD = 1000;

// Sequential Bubble Sort
void sequentialBubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < n - i - 1; ++j)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}

// Parallel Bubble Sort using OpenMP (Odd-Even)
void parallelBubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n; ++i) {
        #pragma omp parallel for
        for (int j = i % 2; j < n - 1; j += 2) {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}

// Merge utility
void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right)
        temp[k++] = (arr[i] < arr[j]) ? arr[i++] : arr[j++];
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    for (int i = left; i <= right; ++i)
        arr[i] = temp[i - left];
}

// Sequential Merge Sort
void sequentialMergeSort(vector<int>& arr, int left, int right) {
    if (left >= right) return;
    int mid = (left + right) / 2;
    sequentialMergeSort(arr, left, mid);
    sequentialMergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// Parallel Merge Sort with threshold
void parallelMergeSort(vector<int>& arr, int left, int right) {
    if (left >= right) return;
    if (right - left < MERGE_SORT_THRESHOLD) {
        sequentialMergeSort(arr, left, right);
        return;
    }

    int mid = (left + right) / 2;

    #pragma omp parallel sections
    {
        #pragma omp section
        parallelMergeSort(arr, left, mid);

        #pragma omp section
        parallelMergeSort(arr, mid + 1, right);
    }

    merge(arr, left, mid, right);
}

// Main function
int main() {
    int n = 100000; // size of input
    vector<int> inputData(n);
    for (int i = 0; i < n; ++i)
        inputData[i] = rand() % 100000; // fill with random numbers

    int choice;
    while (true) {
        cout << "\n==== Sorting Menu ====\n";
        cout << "1. Sequential Bubble Sort\n";
        cout << "2. Parallel Bubble Sort\n";
        cout << "3. Sequential Merge Sort\n";
        cout << "4. Parallel Merge Sort\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice >= 1 && choice <= 4) {
            vector<int> temp = inputData; // copy for sorting
            auto start = high_resolution_clock::now();

            switch (choice) {
                case 1:
                    sequentialBubbleSort(temp);
                    break;
                case 2:
                    parallelBubbleSort(temp);
                    break;
                case 3:
                    sequentialMergeSort(temp, 0, temp.size() - 1);
                    break;
                case 4:
                    parallelMergeSort(temp, 0, temp.size() - 1);
                    break;
            }

            auto end = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(end - start);
            cout << "Execution Time: " << duration.count() << " ms\n";

            // Optional: Print sorted array (comment out if too large)
            // for (int i = 0; i < 50 && i < temp.size(); ++i)
            //     cout << temp[i] << " ";
            // cout << (temp.size() > 50 ? "..." : "") << "\n";
        }
        else if (choice == 5) {
            cout << "Exiting...\n";
            break;
        }
        else {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}

