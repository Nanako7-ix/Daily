#ifndef TOPK_TESTER
#define TOPK_TESTER
#include <bits/stdc++.h>

using u32 = unsigned;
using u64 = unsigned long long;
using i64 = long long;


// create a random vector with n elements and a unsigned integer k <= n
// elements range: [0, V = 1e9)
// random engine: mt19937_64
// random seed: std::chrono::steady_clock::now().time_since_epoch().count()
std::pair<std::vector<int>, u64> random_TopK(u64 n, int V = 1e9, bool Hitbound = false) {
    static std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::vector<int> a(n);
    for(u64 i = 0; i < n; ++i) {
        a[i] = rng() % V;
    }
    if (Hitbound) {
        a[rng() % n] = V;
    }
    return { a, rng() % n + 1 };
}


// func: the function to be tested
// test the time of **func** on solving Top K
// TestCase: MaxTest = 20
u64 testTopK (
    u64 n,
    int (*func)(std::vector<int>::iterator, std::vector<int>::iterator, u64 k),
    int V = 1e9,
    bool Hitbound = false,
    const u32 MaxTest = 20
) {
    i64 sum = 0;
    std::cout << "\n[                    ]  0 %";
    std::cout.flush();
    for(u32 T = 1; T <= MaxTest; ++T) {
        auto [a, k] = random_TopK(n, V, Hitbound);
        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        func(a.begin(), a.end(), k);
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
        std::cout << "]  " << u32(100.0 * T / MaxTest) << " %";
        std::cout.flush();
    }
    std::cout << std::endl;
    return sum / MaxTest;
}
#endif