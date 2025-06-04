/**
 * Author: Nanako7_ix
 * Created: 2025/04/19 23:18:28
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
    vector<vector<int>> a(n + 1, vector<int> (n + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> a[i][j];
        }
    }
    
    vector<array<int, 3>> ok;
    vector<array<i64, 2>> dp;

    ok.assign(n + 1, {1, 1, 1});
    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (a[i][j] == a[i - 1][j] + 1) {
                ok[i][2] = 0;
            }
            if (a[i][j] == a[i - 1][j] + 0) {
                ok[i][1] = 0;
            }
            if (a[i][j] == a[i - 1][j] - 1) {
                ok[i][0] = 0;
            }
        }
    }
    
    dp.assign(n + 1, {INF, INF});
    cin >> dp[1][1];
    dp[1][0] = 0;
    for (int i = 2; i <= n; ++i) {
        i64 x; cin >> x;
        if (ok[i][0]) {
            dp[i][1] = min(dp[i][1], dp[i - 1][0] + x);
        }
        if (ok[i][1]) {
            dp[i][1] = min(dp[i][1], dp[i - 1][1] + x);
            dp[i][0] = min(dp[i][0], dp[i - 1][0]);
        }
        if (ok[i][2]) {
            dp[i][0] = min(dp[i][0], dp[i - 1][1]);
        }
    }
    i64 ans1 = min(dp[n][0], dp[n][1]);

    ok.assign(n + 1, {1, 1, 1});
    for (int i = 1; i <= n; ++i) {
        for (int j = 2; j <= n; ++j) {
            if (a[i][j] == a[i][j - 1] + 1) {
                ok[j][2] = 0;
            }
            if (a[i][j] == a[i][j - 1] + 0) {
                ok[j][1] = 0;
            }
            if (a[i][j] == a[i][j - 1] - 1) {
                ok[j][0] = 0;
            }
        }
    }
    
    dp.assign(n + 1, {INF, INF});
    cin >> dp[1][1];
    dp[1][0] = 0;
    for (int i = 2; i <= n; ++i) {
        i64 x; cin >> x;
        if (ok[i][0]) {
            dp[i][1] = min(dp[i][1], dp[i - 1][0] + x);
        }
        if (ok[i][1]) {
            dp[i][1] = min(dp[i][1], dp[i - 1][1] + x);
            dp[i][0] = min(dp[i][0], dp[i - 1][0]);
        }
        if (ok[i][2]) {
            dp[i][0] = min(dp[i][0], dp[i - 1][1]);
        }
    }
    i64 ans2 = min(dp[n][0], dp[n][1]);

    if (ans1 + ans2 >= INF) {
        cout << "-1\n";
    } else {
        cout << ans1 + ans2 << endl;
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