// Author: Nanako7_ix
// Created: 2025/04/04 00:12:07
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

i64 f[65][505];

void solve() {
    i64 l, r, x;
    cin >> l >> r >> x;
    i64 t = 1;
    while(4 * t + 1 <= l) {
        t <<= 2;
        t += 1;
    }
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
    int T = 1;
    cin >> T;
    f[1][1] = 1, f[1][2] = 2, f[1][3] = 3, f[1][4] = 4;
    int fst = 1;
    for(int i = 2; i <= 60; ++i) {
        for(int j = 1; j <= 505; ++j) {
            f[i][j + 1] += f[i - 1][j];
            f[i][j + 2] += f[i - 1][j];
            f[i][j + 3] += f[i - 1][j];
        }
        f[i][fst + ]
    }
    while(T--) solve();
    return 0;
}