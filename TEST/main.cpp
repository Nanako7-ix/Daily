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
    for(int n : {100000, 200000, 300000, 400000, 500000}) {
        std::cout << "n = " << n << std::endl;
        std::cout << "Sort1: " << testSort(n, SelectionSort) << "ms" << std::endl;
        std::cout << "Sort2: " << testSort(n, BubbleSort) << "ms" << std::endl;
        std::cout << "Sort3: " << testSort(n, InsertionSort) << "ms" << std::endl;
        std::cout << "Sort4: " << testSort(n, MergeSort) << "ms" << std::endl;
        std::cout << "Sort5: " << testSort(n, QuickSort) << "ms" << std::endl;
        std::cout << std::endl;
    }
    /*---------------------------------------------------------*/

    /*--------------------------Task2--------------------------*/
    // for(int n : {10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000}) {
    //     std::cout << "n = " << n << std::endl;
    //     std::cout << testSort(n, SelectionSort) << " " << testSort(n, BubbleSort) << " " << testSort(n, InsertionSort) << std::endl;
    //     std::cout << std::endl;
    // }
    /*---------------------------------------------------------*/

    /*--------------------------Task3--------------------------*/
    // for(int n : {10, 20, 30, 40, 50, 60, 70, 80, 90}) {
    //     std::cout << "n = " << n << std::endl;
    //     std::cout << testSort(n, MergeSort) << " " << testSort(n, QuickSort) << std::endl;
    //     std::cout << std::endl;
    // }
    /*---------------------------------------------------------*/

    /*--------------------------Task4--------------------------*/
    // for(u64 n : {100000000, 200000000, 300000000, 400000000, 500000000}) {
    //     std::cout << "n = " << n << std::endl;
    //     std::cout << "AfterSort: " << testTopK(n, AfterSort) << std::endl;
    //     std::cout << "MaintainHeap: " << testTopK(n, MaintainHeap) << std::endl;
    //     std::cout << "QuickSelect: " << testTopK(n, QuickSelect) << std::endl;
    // }
    /*---------------------------------------------------------*/
    return 0;
}