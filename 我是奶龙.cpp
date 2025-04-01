// Author: Nanako7_ix
// Created: 2025/03/29 14:52:59
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

void solve() {
    array<i64, 3> a {};
    cin >> a[0] >> a[1] >> a[2];
    a[0] %= 3, a[1] %= 3, a[2] %= 3;
    sort(a.begin(), a.end());
    if(a[0] == a[1] || a[1] == a[2]) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}