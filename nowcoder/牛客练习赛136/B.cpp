// Author: Nanako7_ix
// Created: 2025/04/03 19:04:48
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


void solve() {
    int n;
    cin >> n;
    vector<int> f;
    for(int i = 1; i <= n; ++i) {
        if(i % 3 == 0 || i % 37 == 0) {
            f.push_back(i);
        }
    }
    if(f.size() * 3 >= n) {
        vector<int> a(n + 1), vis(n + 1);
        for(int i = 2; i <= n; i += 3) {
            a[i] = f[i / 3];
            vis[f[i / 3]] = 1;
        }
        for(int i = 1, j = 1; i <= n; ++i) {
            if(a[i]) continue;
            while(vis[j]) ++j;
            a[i] = j, vis[j] = 1;
        }
        for(int i = 1; i <= n; ++i) {
            cout << a[i] << " \n"[i == n];
        }
    } else {
        cout << "Baka!\n";
    }
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}