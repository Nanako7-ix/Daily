// Author: Nanako7_ix
// Created: 2025/03/29 15:37:43
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
    int n, m = 0;
    cin >> n;
    vector<array<int, 2>> a(n + 1);
    for(int i = 1; i <= n; ++i) {
        int x, y, z;
        cin >> x >> y >> z >> a[i][1];
        a[i][0] = x + y + z;
        m = max(m, a[i][1]);
    }

    sort(a.begin() + 1, a.end(), [](array<int, 2> x, array<int, 2> y) {
        return x[1] < y[1];
    });

    vector<int> dp(m + 1);
    for(int i = 1; i <= n; ++i) {
        for(int j = a[i][1] - a[i][0]; j >= 0; --j) {
            dp[j + a[i][0]] = max(dp[j + a[i][0]], dp[j] + 1);
        }
    }
    cout << *max_element(dp.begin(), dp.end()) << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}