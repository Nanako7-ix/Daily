// Author: Nanako7_ix
// Created: 2025/04/09 19:51:53
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

bool check(int x) {
    if(x <= 1) return false;
    for(int i = 2; i64(i) * i <= x; ++i) {
        if(x % i == 0) return false;
    }
    return true;
}

void solve() {
    int n, k;
    cin >> n >> k;
    if (n == 1) {
        int n = 0;
        for(int i = 1; i <= k; ++i) {
            n = n * 10 + 1;
        }
        if(check(n)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
        return;
    }
    if(k != 1 || !check(n)) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
    }
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
    
    int T = 1;
    cin >> T;
    
    while (T--) {
        solve();
    }
    
    return 0;
}