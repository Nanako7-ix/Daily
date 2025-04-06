#ifndef SORT_TESTER
#define SORT_TESTER
#include <bits/stdc++.h>

using u32 = unsigned;
using u64 = unsigned long long;
using i64 = long long;


// create a random vector with n elements
// elements range: [0, V = 1e9)
// random engine: mt19937_64
// random seed: std::chrono::steady_clock::now().time_since_epoch().count()
std::vector<int> random_Sort(
    u64 n,
    int V = 1e9
) {
    static std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::vector<int> a(n);
    for(u64 i = 0; i < n; ++i) {
        a[i] = rng() % V;
    }
    return a;
}


// func: the function to be tested
// test the time of **func** on sorting n elements
// TestCase: MaxTest = 20
u64 testSort(
    u64 n,
    void (*func)(std::vector<int>::iterator, std::vector<int>::iterator),
    const u32 MaxTest = 20
) {
    i64 sum = 0;
    std::cout << "\n[                    ]  0 %";
    std::cout.flush();
    for(u32 T = 1; T <= MaxTest; ++T) {
        auto a = random_Sort(n);
        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        func(a.begin(), a.end());
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        int t = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        sum += t;

        std::cout << "\r[";
        for (u32 i = 1; i <= MaxTest; ++i) {
            if (i <= T) {
                std::cout << "#";
            } else {
                std::cout << " ";
            }
        }
        std::cout << "]  " << u32(100.0 * T / MaxTest) << "%";
        std::cout.flush();
    }
    std::cout << std::endl;
    return sum / MaxTest;
}
#endif