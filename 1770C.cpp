// Author: Nanako7_ix
// Created: 2025/03/29 18:07:50
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
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

constexpr int primes[] = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97 };

void solve() {
    int n;
    cin >> n;
    vector<i64> a(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    map<i64, set<int>> occur;
    for(int i = 1; i <= n; ++i) {
        for(int j = i + 1; j <= n; ++j) {
            if(a[i] == a[j]) {
                cout << "NO\n";
                return;
            }
            i64 x = std::abs(a[i] - a[j]);
            for(auto p : primes) {
                if(p > x) break;
                if(x % p == 0) {
                    occur[p].insert((-a[i] % p + p) % p);
                    occur[p].insert((-a[j] % p + p) % p);
                    while(x % p == 0) x /= p;
                }
            }
        }
    }
    for(auto [x, S] : occur) {
        if((int) S.size() == x) {
            cout << "No\n";
            return;
        }
    }
    cout << "YES\n";
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}