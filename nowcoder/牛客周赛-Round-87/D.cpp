// Author: Nanako7_ix
// Created: 2025/03/30 19:27:22
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
    vector<i64> dp(n + 1, -INF);
    dp[0] = 0;
    for(int i = 1; i <= n; ++i) {
        i64 x; cin >> x;
        dp[i] = max(dp[i - 1] + x, dp[i]);
        if(i - 2 >= 0) dp[i] = max(dp[i - 2], dp[i]);
        if(i - 3 >= 0) dp[i] = max(dp[i - 3], dp[i]);
    }
    cout << dp[n] << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}