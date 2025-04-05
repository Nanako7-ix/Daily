// Author: Nanako7_ix
// Created: 2025/04/05 20:53:14
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define setpre(x) fixed << setprecision(x)
#define debug(x) cerr << #x << " = " << x << "\n"
#define endl "\n"
using namespace std;
using namespace __gnu_pbds;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

constexpr int inf = 0x3f3f3f3f;
constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;
constexpr int N = 1E6;

vector<int> minp, primes;
void sieve(int N) {
    minp.assign(N + 1, 0);
    primes.clear();
    for(int i = 2; i <= N; ++i) {
        if(!minp[i]) primes.emplace_back(minp[i] = i);
        for(auto p : primes) {
            if(i * p > N) break;
            minp[i * p] = p;
            if(i % p == 0) break;
        }
    }
}

vector<int> f;

void solve() {
    i64 n;
    cin >> n;
    i64 t = sqrt(n);
    while((t + 1) * (t + 1) <= n) ++t;
    while(t * t > n) --t;
    i64 x = *prev(upper_bound(f.begin(), f.end(), t));
    cout << x * x << endl;
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
    
    int T = 1;
    cin >> T;
    
    sieve(N);
    for(int i = 2; i <= N; ++i) {
        int x = i;
        int t1 = minp[x];
        while(x % t1 == 0) x /= t1;
        if(x == 1) continue;
        int t2 = minp[x];
        while(x % t2 == 0) x /= t2;
        if(x == 1) {
            f.push_back(i);
        }
    }

    while (T--) {
        solve();
    }
    
    return 0;
}