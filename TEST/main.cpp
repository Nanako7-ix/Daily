#include <bits/stdc++.h>
#include "Sort.hpp"
#include "SortTester.hpp"
#include "TopK.hpp"
#include "TopKTester.hpp"

using u32 = unsigned;
using u64 = unsigned long long;
using i64 = long long;

int main() {
    /*--------------------------Task1--------------------------*/
    // std::cout << "Task1\n";
    // for(int n : {100000, 200000, 300000, 400000, 500000}) {
    //     std::cout << "n = " << n << std::endl;
    //     std::cout << "SelectionSort:\t" << testSort(n, SelectionSort) << "\tms" << std::endl;
    //     std::cout << "BubbleSort:\t" << testSort(n, BubbleSort) << "\tms" << std::endl;
    //     std::cout << "InsertionSort:\t" << testSort(n, InsertionSort) << "\tms" << std::endl;
    //     std::cout << "MergeSort:\t" << testSort(n, MergeSort) << "\tms" << std::endl;
    //     std::cout << "QuickSort:\t" << testSort(n, QuickSort) << "\tms" << std::endl;
    //     std::cout << std::endl;
    // }
    /*---------------------------------------------------------*/

    /*--------------------------Task2--------------------------*/
    // std::cout << "Task2\n";    
    // for(int n : {10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000}) {
    //     std::cout << "n = " << n << std::endl;
    //     std::cout << "SelectionSort:\t" << testSort(n, SelectionSort) << "\tms" << std::endl;
    //     std::cout << "BubbleSort:\t" << testSort(n, BubbleSort) << "\tms" << std::endl;
    //     std::cout << "InsertionSort:\t" << testSort(n, InsertionSort) << "\tms" << std::endl;
    //     std::cout << std::endl;
    // }
    /*---------------------------------------------------------*/

    /*--------------------------Task3--------------------------*/
    // std::cout << "Task3\n";
    // for(int n : {10000000, 20000000, 30000000, 40000000, 50000000, 60000000, 70000000, 80000000, 90000000}) {
    //     std::cout << "n = " << n << std::endl;
    //     std::cout << "MergeSort:\t" << testSort(n, MergeSort) << "\tms" << std::endl;
    //     std::cout << "QuickSort:\t" << testSort(n, QuickSort) << "\tms" << std::endl;
    //     std::cout << std::endl;
    // }
    /*---------------------------------------------------------*/

    /*--------------------------Task4--------------------------*/
    for(u64 n : {1000000000ULL, 2000000000ULL, 3000000000ULL, 4000000000ULL, 5000000000ULL}) {
        std::cout << "n = " << n << std::endl;
        std::cout << "AfterSort: " << testTopK(n, AfterSort, 1E9) << std::endl;
        std::cout << "MaintainHeap: " << testTopK(n, MaintainHeap, 1E9) << std::endl;
        std::cout << "QuickSelect: " << testTopK(n, QuickSelect, 1E9) << std::endl;
    }
    /*---------------------------------------------------------*/

    /*--------------------------Task4--------------------------*/
    for(u64 V : {1000000, 10000000, 100000000, 1000000000}) {
        std::cout << "V = " << V << std::endl;
        std::cout << "QuickSelect: " << testTopK(5E9, QuickSelect, V, true) << std::endl;
        std::cout << "OpenBucket: " << testTopK(5E9, OpenBucket, V, true) << std::endl;
    }
    /*---------------------------------------------------------*/
    return 0;
}