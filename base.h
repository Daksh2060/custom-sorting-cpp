#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Operator for printing vectors.
template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v){

    int n = v.size();
    os << "{";
    for (int i = 0; i < v.size(); i++){

        os << v[i];
        if (i < n - 1){

            os << ", ";
        }
    }
    os << "}";
    return os;
}

/*
 SortStats stores statistics about one run of a sorting routine.
 "ulong" is used to shorten "unsigned long"
*/
typedef unsigned long ulong;

struct SortStats{

    string sort_name;
    size_t vector_size = 0;
    ulong num_comparisons = 0;
    double cpu_running_time_sec = 0.0;

    string to_csv() const{

        return sort_name + ", " + to_string(vector_size) + ", " + to_string(num_comparisons) + ", " + to_string(cpu_running_time_sec);
    }
};

// Operator for printing SortStats objects.
ostream &operator<<(ostream &os, const SortStats &ss){

    os << "SortStats{" << ss.sort_name
       << ", size=" << ss.vector_size
       << ", num_comparisons=" << ss.num_comparisons
       << ", cpu_running_time_sec=" << ss.cpu_running_time_sec
       << "}";
    return os;
}

/*
 Returns true if v[0] <= v[1] <= ... <= v[n-1], and false otherwise.
 Returns true if v is empty, i.e. an empty vector is considered sorted.
*/
template <typename T>
bool is_sorted(vector<T> &v);

/*
 Sorting algorithm headers. Each algorithm implements the named algorithm, and
 returns a SortStats object containing statistics about the sorting run.
*/

/* 
 Bubble Sort: Compares and swaps adjacent elements until the entire array is sorted.
 Inefficient for large datasets.
 Quadratic time complexity O(n^2).
*/
template <typename T>
SortStats bubble_sort(vector<T> &v);

/*
 Insertion Sort: Builds the final sorted array one item at a time.
 Efficient for small datasets or nearly sorted data.
 Quadratic time complexity O(n^2) in the worst case.
*/
template <typename T>
SortStats insertion_sort(vector<T> &v);

/*
 Selection Sort: Finds the minimum element from the unsorted part and swaps it with the first element.
 Repeats until the entire array is sorted.
 Quadratic time complexity O(n^2).
*/
template <typename T>
SortStats selection_sort(vector<T> &v);

/*
 Merge Sort: Divides the array into two halves, recursively sorts them, and then merges them.
 Guaranteed O(n log n) time complexity.
 Requires additional space.
*/
template <typename T>
SortStats merge_sort(vector<T> &v);

/*
 Quick Sort: Chooses a pivot, partitions the array into two halves,
 and recursively sorts each half.
 Average-case O(n log n) time complexity.
*/
template <typename T>
SortStats quick_sort(vector<T> &v);

/*
 Shell Sort: An extension of insertion sort that allows for swapping elements
 that are far apart. Reduces the distance between elements gradually.
 Time complexity varies but often better than O(n^2).
*/
template <typename T>
SortStats shell_sort(vector<T> &v);

/*
 Improved Quick Sort (Iquick Sort): An optimized version of Quick Sort that switches
 to Insertion Sort for small subarrays to reduce overhead.
 Average-case O(n log n) time complexity.
*/
template <typename T>
SortStats iquick_sort(vector<T> &v);

// Returns a vector of n randomly chosen ints, each <= max and >= min.
vector<int> rand_vec(int n, int min, int max);
