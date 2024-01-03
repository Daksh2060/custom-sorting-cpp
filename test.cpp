#include <iostream>
#include <fstream>
#include <vector>
#include "base.h"
#include "sort_implementations.h"
#include <cassert>
#include <string>
#include <random>

using namespace std;

std::vector<int> rand_vec(int n, int min, int max) {
    std::vector<int> result;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(min, max);
    
    for (int i = 0; i < n; ++i) {
        result.push_back(dis(gen));
    }
    
    return result;
}

std::string generateRandomString(int length) {
    const std::string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ";
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, charset.length() - 1);

    std::string randomString;
    for (int i = 0; i < length; ++i) {
        randomString += charset[distribution(generator)];
    }

    return randomString;
}

std::vector<std::string> generateRandomStrings(int n, int length) {
    std::vector<std::string> randomStrings;
    for (int i = 0; i < n; ++i) {
        randomStrings.push_back(generateRandomString(length));
    }
    return randomStrings;
}

int main(){

    std::ofstream outputFile("sorting_results.csv");
    outputFile << "Sorting Name, N, Comparisons, Seconds" << std::endl;

    std::vector<int> arr[25];

    for(int i = 2000, j = 0; i <= 50000; i += 2000, j++){
        std::vector<int> randomVector = rand_vec(i, 0, 50000);
        arr[j] = randomVector;
    }

    for(int i = 0; i < 25; i++){

        std::vector<int> test_copy = arr[i];
        SortStats test = bubble_sort(test_copy);
        assert(is_sorted(test_copy));
        string print = test.to_csv();
        outputFile << print << std::endl;
    }
    
    for(int i = 0; i < 25; i++){

        std::vector<int> test_copy = arr[i];
        SortStats test = insertion_sort(test_copy);
        assert(is_sorted(test_copy));
        string print = test.to_csv();
        outputFile << print << std::endl;
    }

    for(int i = 0; i < 25; i++){

        std::vector<int> test_copy = arr[i];
        SortStats test = selection_sort(test_copy);
        assert(is_sorted(test_copy));
        string print = test.to_csv();
        outputFile << print << std::endl;
    }

    for(int i = 0; i < 25; i++){

        std::vector<int> test_copy = arr[i];
        SortStats test = merge_sort(test_copy);
        assert(is_sorted(test_copy));
        string print = test.to_csv();
        outputFile << print << std::endl;
    }

    for(int i = 0; i < 25; i++){

        std::vector<int> test_copy = arr[i];
        SortStats test = quick_sort(test_copy);
        assert(is_sorted(test_copy));
        string print = test.to_csv();
        outputFile << print << std::endl;
    }

    for(int i = 0; i < 25; i++){

        std::vector<int> test_copy = arr[i];
        SortStats test = shell_sort(test_copy);
        assert(is_sorted(test_copy));
        string print = test.to_csv();
        outputFile << print << std::endl;
    }

    for(int i = 0; i < 25; i++){

        std::vector<int> test_copy = arr[i];
        SortStats test = iquick_sort(test_copy);
        assert(is_sorted(test_copy));
        string print = test.to_csv();
        outputFile << print << std::endl;
    }

    return 0;
}