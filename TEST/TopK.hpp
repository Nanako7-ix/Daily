#ifndef TOPK_H
#define TOPK_H
#include <bits/stdc++.h>
#include "Sort.hpp"

using i64 = long long;
using u32 = unsigned;
using u64 = unsigned long long;

template<typename Iterator, typename T = std::iterator_traits<Iterator>::value_type>
T AfterSort(Iterator l, Iterator r, u64 k) {
    QuickSort(l, r);
    return *(l + k - 1);
}

template<typename Iterator, typename T = std::iterator_traits<Iterator>::value_type>
T MaintainHeap(Iterator l, Iterator r, u64 k) {
    std::vector<T> heap(l, l + k);
    std::make_heap(heap.begin(), heap.end());
    for (Iterator it = l + k; it < r; ++it) {
        if (*it < heap[0]) {
            std::pop_heap(heap.begin(), heap.end());
            heap.back() = *it;
            std::push_heap(heap.begin(), heap.end());
        }
    }
    return heap[0];
}

template<typename Iterator, typename T = std::iterator_traits<Iterator>::value_type>
T OpenBucket (Iterator l, Iterator r, u64 k) {
    T m = *std::max_element(l, r);
    std::vector<T> cnt(m + 1);
    for (Iterator it = l; it < r; ++it) {
        cnt[*it]++;
    }
    u64 now = 0;
    for (int i = 0; i <= m; ++i) {
        now += cnt[i];
        if(now >= k) return i;
    }
}

template<typename Iterator, typename T = std::iterator_traits<Iterator>::value_type>
T QuickSelect (Iterator l, Iterator r, u64 k) {
    assert(r - l != 0);
    if(r - l == 1) return *l;
    Iterator poivt;
    for(Iterator i = l, j = r - 1; i < j; ) {
        while(i - j < 0 && *i <= *j) --j;
        std::iter_swap(i, j);
        while(i - j < 0 && *i <= *j) ++i;
        std::iter_swap(i, j);
        if(i == j) poivt = i;
    }
    u64 lft = poivt - l;
    if(lft >= k) return QuickSelect(l, poivt, k);
    if(lft == k - 1) return *poivt;
    return QuickSelect(poivt + 1, r, k - lft - 1);
}
#endif