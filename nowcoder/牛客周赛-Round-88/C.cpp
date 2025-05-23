// Author: Nanako7_ix
// Created: 2025/04/06 19:06:33
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
    int Xa, Ya, Xb, Yb, Xc, Yc;
    cin >> Xa >> Ya >> Xb >> Yb >> Xc >> Yc;
    if(
        2 * Xa == Xb + Xc ||
        2 * Xb == Xa + Xc ||
        2 * Xc == Xa + Xb ||
        2 * Ya == Yb + Yc ||
        2 * Yb == Ya + Yc ||
        2 * Yc == Ya + Yb
    ) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
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