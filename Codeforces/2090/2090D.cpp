// Author: Nanako7_ix
// Created: 2025/04/06 20:51:50
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

void solve() {
    int n;
    cin >> n;
    for(auto p : primes) {
        int len = min(p, n - p + 1);
        if(len * 2 - 1 >= n / 3 - 1) {
            vector<int> a(n + 1), vis(n + 1);
            vis[a[1] = p] = 1;
            for(int i = 1, j = 2; ; j += 2, ++i) {
                if(p + i > n || p - i < 1) break;
                vis[a[j] = p - i] = 1;
                vis[a[j + 1] = p + i] = 1;
            }
            for(int i = 1, j = 1; i <= n; ++i) {
                if(a[i] == 0) {
                    while(vis[j]) ++j;
                    vis[a[i] = j] = 1;
                }
                cout << a[i] << " \n"[i == n];
            }
            return;
        }
    }
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
    
    int T = 1;
    cin >> T;

    sieve(100000);

    while (T--) {
        solve();
    }
    
    return 0;
}