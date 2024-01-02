#pragma once

#include "a4_base.h"

using namespace std;

/* 
 Bubble Sort: Compares and swaps adjacent elements until the entire array is sorted.
 Inefficient for large datasets.
 Quadratic time complexity O(n^2).
 Stable and in-place.
*/
template <typename T>
SortStats bubble_sort(vector<T> &v){

    //Start timer and accumulator for comparisons
    ulong num_comps = 0; 
    clock_t start = clock(); 

    //For each item of the array
    for(int i = 0; i < v.size(); i++){

        //Compare the item to every other item in the array
        for(int j = 0; j < v.size() - 1; j++){

            num_comps++;

            //Swap the item forward until it is in right place
            if(v[j] > v[j + 1]){

                T temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
    
    //End clock to get time of sorting
    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;

    //Return object with sorting name, size of vector, comparisons, and runtime
    return SortStats{"Bubble sort", v.size(), num_comps, elapsed_cpu_time_sec};
}

/*
 Insertion Sort: Builds the final sorted array one item at a time.
 Efficient for small datasets or nearly sorted data.
 Quadratic time complexity O(n^2) in the worst case.
*/
template <typename T>
SortStats insertion_sort(vector<T> &v){

    //Start timer and accumulator for comparisons
    ulong num_comps = 0; 
    clock_t start = clock();

    //Create an index and current value tracker
    int index;
    T current;

    //For each element, check the previous one
    for(int i = 1; i < v.size(); i++){

        current = v[i];
        index = i - 1;
 
        //Continue to switch back until the previous is no longer larger
        while(index >= 0 && v[index] > current){

            v[index + 1] = v[index];
            index --;
            num_comps++;
        }

        v[index + 1] = current;
    }

    //End clock to get time of sorting
    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;
    
    return SortStats{"Insertion sort", v.size(), num_comps, elapsed_cpu_time_sec};
}

/*
 Selection Sort: Finds the minimum element from the unsorted part and swaps it with the first element.
 Repeats until the entire array is sorted.
 Quadratic time complexity O(n^2).
*/
template <typename T>
SortStats selection_sort(vector<T> &v){

    ulong num_comps = 0; 
    clock_t start = clock();

    //Get size of vector to be sorted
    int n = v.size();

    //Find the smallest value in the vector
    for(int i = 0; i < n - 1; ++i){

        int min_idx = i;

        for(int j = i + 1; j < n; ++j){

            //Compare the smallest value with current index
            num_comps++;

            if(v[j] < v[min_idx]){

                min_idx = j;
            }
        }
        
        //If the current index is not the smallest, switch them
        if(min_idx != i){

            std::swap(v[i], v[min_idx]);
        }
    }

    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;
    
    return SortStats{"Selection sort", v.size(), num_comps, elapsed_cpu_time_sec};
}

//Merge helper function used to merge 2 sorted vectors into 1
template <typename T>
vector<T> merge(vector<T> &v1, vector<T> &v2, ulong &num_comps){

    //Create an empty vector to store new sorted array
    vector<T> v;

    //Declare indices for both halves of the vector
    int i = 0;
    int j = 0;

    //Compare both vectors 1 index at a time
    while(i < v1.size() && j < v2.size()){

        num_comps++;

        //Add the smaller of the two indices to the end of new vector
        if(v1[i] < v2[j]){

            v.push_back(v1[i]);
            i++;
        }

        else{

            v.push_back(v2[j]);
            j++;
        }
    }

    //If there are left overs in the first vector, add them to new vector
    while(i < v1.size()){

        v.push_back(v1[i]);
        i++;
    }

    //If there are left overs in the second vector, add them to new vector
    while(j < v2.size()){

        v.push_back(v2[j]);
        j++;
    }

    return v;
}

//Helper function for merge sort which can take more arguments
template <typename T>
void merge_sort_helper(vector<T> &v, ulong &num_comps){

    //If there is only 1 item in vector, return
    if(v.size() <= 1){

        return;
    }

    //Else make the middle point half the size of vector
    int mid = v.size() / 2;

    //Split vector into 2 halves
    vector<T> v1(v.begin(), v.begin() + mid);
    vector<T> v2(v.begin() + mid, v.end());

    //Recursively call on both halves
    merge_sort_helper(v1, num_comps);
    merge_sort_helper(v2, num_comps);

    //Once vector has been split, start recombining
    v = merge(v1, v2, num_comps);
}

/*
 Merge Sort: Divides the array into two halves, recursively sorts them, and then merges them.
 Guaranteed O(n log n) time complexity.
 Requires additional space.
 Primary function of merge sort only used to call helper
*/
template <typename T>
SortStats merge_sort(vector<T> &v){

    ulong num_comps = 0; 
    clock_t start = clock();

    //Helper for merge sort which also takes reference of accumulator
    merge_sort_helper(v, num_comps);

    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;
    
    return SortStats{"Merge sort", v.size(), num_comps, elapsed_cpu_time_sec};
}

//Partition helper function used for selection pivots
template <typename T>
int partition(vector<T> &v, int start, int end, ulong &num_comps){

    //Pivot used will be last item of the vector
    T pivot = v[end];

    //Set to i to track position of pivot
    int i = start;

    //Compare each element to the pivot element
    for(int j = start; j < end; j++){   

        num_comps++;

        //Move all elements less than pivot to one side
        if(v[j] < pivot){

            swap(v[i], v[j]);
            i++;
        }
    }

    //Swap the pivot and the start index
    swap(v[i], v[end]);

    //Returns the index position of the pivot
    return i;
}

//Quick sort helper used to take more arguments
template <typename T>
void quick_sort_helper(vector<T>& v, int start, int end, ulong &num_comps){

    //If the vector is empty or only has 1 element, return
    if(start >= end){

        return;
    }

    //Choose a pivot index using partition
    int pivot = partition(v, start, end, num_comps);

    //Recursively call helper function
    quick_sort_helper(v, start, pivot - 1, num_comps);
    quick_sort_helper(v, pivot + 1, end, num_comps);
}

/*
 Quick Sort: Chooses a pivot, partitions the array into two halves,
 and recursively sorts each half.
 Average-case O(n log n) time complexity.
 Primary function for quick sort used to call helper
*/
template <typename T>
SortStats quick_sort(vector<T> &v){

    ulong num_comps = 0; 
    clock_t start = clock();

    //Call helper function and pass comparisons as reference
    quick_sort_helper(v, 0, v.size() - 1, num_comps);

    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;
    
    return SortStats{"Quick sort", v.size(), num_comps, elapsed_cpu_time_sec};
}

/*
 Shell Sort: An extension of insertion sort that allows for swapping elements
 that are far apart. Reduces the distance between elements gradually.
 Time complexity varies but often better than O(n^2).
*/
template <typename T>
SortStats shell_sort(vector<T> &v){

    ulong num_comps = 0; 
    clock_t start = clock();

    int n = v.size();

    //Loop continually halves the vector into smaller pieces using gaps
    for(int gap = n/2; gap > 0; gap /= 2){

        //Start a loop at each gap point
        for (int i = gap; i < n; i += 1){

            //Create a copy of item at the gap point
            T temp = v[i];

            int j;
            //Continually shift the item at the gap until its at the right index
            for(j = i; j >= gap && v[j - gap] > temp; j -= gap){

                v[j] = v[j - gap];
                num_comps++;
            }
              
            //Put the temporary item in correct place
            v[j] = temp;
        }
    }

    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;
    
    return SortStats{"Shell sort", v.size(), num_comps, elapsed_cpu_time_sec};
}

//Helper function for insertion sort used in iquick sort 
template <typename T>
void iquick_insertion_helper(vector<T> &v, int low, int high, ulong &num_comps){
    
    //For each item in the vector
    for(int i=low+1;i<high+1;i++){

        //Create a copy of item and track index
        T val = v[i] ;
        int j = i ;

        //If the item before the current is larger, switch back until in right place, switch item
        while(j>low && v[j-1]>val){

            num_comps++;
            v[j]= v[j-1] ;
            j-= 1;
        }

        //The item is put at correct index 
        v[j]= val ;
    }
}

//Helper function used to choose pivot for iquick sort
template <typename T>
int iquick_partition(vector<T> &v, int low, int high, ulong &num_comps){

    //Pivot is the last item
    T pivot = v[high];

    //Create index to keep track of pivot position
    int j = low;
    
    //Check each item in the vector
    for(int i = low; i < high; i++){

        //Move all items less than pivot to one side
        if(v[i]<pivot){

            T temp = v[i];
            v[i] = v[j];
            v[j] = temp;
            j += 1;
        }
        num_comps++;
    }
    
    //Switch pivot item to between the two halves
    T temp = v[j];
    v[j] = v[high];
    v[high] = temp;
    
    //Return pivot index
    return j;
}

//Iquick helper used to take in more arguments than primary function
template <typename T>
void iquick_sort_helper(vector<T> &v, int low, int high, ulong &num_comps){

    //If the vector is not empty
    while(low < high){
    
        //If the vector is smaller in size than the threshold of 10, use insertion sort
        if(high-low + 1 < 10){

            iquick_insertion_helper(v, low, high, num_comps);
            break;
        }
    
        //Else we use quick sort to break vector into smaller sizes
        else{
        
            int pivot = iquick_partition(v, low, high, num_comps);
    
            //If the left of pivot is less than right, sort left part and make new start the middle
            if(pivot-low < high-pivot){

                iquick_sort_helper(v, low, pivot - 1, num_comps);
                low = pivot + 1;
            }

            //If the right of pivot is less than left, sort left part and make new end the middle
            else{
                
                iquick_sort_helper(v, pivot + 1, high, num_comps);
                high = pivot-1;
            }
        }
   }
}

/*
 Improved Quick Sort (Iquick Sort): An optimized version of Quick Sort that switches
 to Insertion Sort for small subarrays to reduce overhead.
 Average-case O(n log n) time complexity.
 Primary function of Iquick sort only used to call helper and track info
*/
template <typename T>
SortStats iquick_sort(vector<T> &v){

    ulong num_comps = 0; 
    clock_t start = clock();

    //Helper called with more arguments, including comparisons passed as reference
    iquick_sort_helper(v, 0, v.size() - 1, num_comps);

    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;
    
    return SortStats{"Iquick sort", v.size(), num_comps, elapsed_cpu_time_sec};
}






