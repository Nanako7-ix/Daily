#ifndef SORT_H
#define SORT_H
#include<bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using u64 = unsigned long long;

// Basic Functions
// iter_swap: swap the elements pointed by two iterators
// inplace_merge: merge two sorted interval in place

// Selection Sort
// [i, r) is unsorted interval
// find the Minimum element in [i, r)
// then swap it with *i
// and [i + 1, r) is unsorted interval
// goto the first step until i == r
template<typename Iterator>
void SelectionSort(Iterator l, Iterator r) {
    for (Iterator i = l; i != r; ++i) {
        Iterator Min = std::min_element(i, r);
        std::iter_swap(i, Min);
    }
}


// Bubble Sort
// [l, i) is unsorted interval
// for all j in [l, i - 1), if element *j is greater than *(j + 1)
// swap *j and *(j + 1)
// and [i - 1, r) is sorted interval
// goto the first step until i == l
template<typename Iterator>
void BubbleSort(Iterator l, Iterator r) {
    for (Iterator i = r; i > l; --i) {
        for(Iterator j = l; j < i - 1; ++j) {
            if(*j > *(j + 1)) std::iter_swap(j, j + 1);
        }
    }
}


// Insertion Sort
// (i, r] is sorted interval
// in order to insert *i to (i, r]
// find the first element p that is greater than *i
// then insert i to the position p
// [i, r] is sorted interval
// goto the first step until i == l
template<typename Iterator>
void InsertionSort(Iterator l, Iterator r) {
    for (Iterator i = r - 2; i >= l; --i) {
        Iterator p = std::lower_bound(i + 1, r, *i);
        for (Iterator j = i; j + 1 != p; ++j) {
            std::iter_swap(j, j + 1);
        }
    }
}


// Merge Sort
// [l, r) is unsorted interval
// divide [l, r) into two subintervals [l, (l + r) / 2) and [(l + r) / 2, r)
// sort the two subintervals
// merge the two sorted subintervals
template<typename Iterator>
void MergeSort(Iterator l, Iterator r) {
    if(r - l <= 1) return;
    u64 len = r - l;
    MergeSort(l, l + (len >> 1));
    MergeSort(l + (len >> 1), r);
    std::inplace_merge(l, l + (len >> 1), r);
}


// Quick Sort
// [l, r) is unsorted interval
// initial poivt is l
// move all elements that are less than *p to the left of p
// move all elements that are greater than *p to the right of p
// divide [l, r) into two subintervals [l, p) and [p, r)
// sort the two subintervals
template<typename Iterator>
void QuickSort(Iterator l, Iterator r) {
    if(r - l <= 1) return;
    for(Iterator i = l, j = r - 1; i < j; ) {
        while(i - j < 0 && *i <= *j) --j;
        std::iter_swap(i, j);
        while(i - j < 0 && *i <= *j) ++i;
        std::iter_swap(i, j);
        if(i == j) {
            QuickSort(l, i), QuickSort(i + 1, r);
        }
    }
}
#endif