// Author: Nanako7_ix
// Created: 2025/04/06 19:35:21
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
    vector<int> a(n + 1), nxt(n + 1, -1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    if(a[n] != 0) nxt[n] = n;
    for(int i = n - 1; i >= 0; --i) {
        nxt[i] = a[i] == 0 ? nxt[i + 1] : i;
    }

    if(a[1] == 0) {
        a[1] = nxt[1] == -1 ? 1 : a[nxt[1]] + nxt[1] - 1;
    }
    for(int i = 2; i <= n; ++i) {
        if(a[i]) continue;
        if(nxt[i] == -1) {
            a[i] = a[i - 1] + 1;
        } else if(a[i - 1] < a[nxt[i]]) {
            a[i] = a[i - 1] + 1;
        } else {
            a[i] = a[i - 1] - 1;
        }
    }
    for(int i = 2; i <= n; ++i) {
        if(std::abs(a[i] - a[i - 1]) != 1) {
            cout << "-1\n";
            return;
        }
    }
    for(int i = 1; i <= n; ++i) {
        cout << a[i] << " \n"[i == n];
    }
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
    
    int T = 1;
    // cin >> T;
    
    while (T--) {
        solve();
    }
    
    return 0;
}