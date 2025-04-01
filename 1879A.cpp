// Author: Nanako7_ix
// Created: 2025/03/26 17:54:22
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
    int n;
    cin >> n;
    vector<array<int, 2>> a(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i][0] >> a[i][1];
    }
    auto [x, y] = a[1];
    sort(a.begin() + 1, a.end());
    for(int i = lower_bound(a.begin() + 1, a.end(), array<int, 2> {x, y}) - a.begin() + 1; i <= n; ++i) {
        if(a[i][1] >= y) {
            cout << "-1\n";
            return;
        }
    }
    cout << x << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}