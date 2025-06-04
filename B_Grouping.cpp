/**
 * Author:  Nanako7_ix
 * Created: 2025/04/30 19:11:56
 * 好想和 めぐる 一起打 xcpc 啊
 */
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
    vector<vector<i64>> a(n + 1, vector<i64> (n + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> a[i][j];
        }
    }
    vector<i64> dp(1 << n);
    for (int s = 1; s < (1 << n); ++s) {
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if ((s >> (i - 1) & 1) && (s >> (j - 1) & 1)) {
                    dp[s] += a[i][j];
                }
            }
        }
        for (int t = s; t > 0; t = (t - 1) & s) {
            dp[s] = max(dp[s], dp[t] + dp[s ^ t]);
        }
    }
    cout << dp[(1 << n) - 1] << endl;
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