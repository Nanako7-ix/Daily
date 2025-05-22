/**
 *
 *  $$$$$$\  $$$$$$\  $$$$$$\  $$\       $$\       $$$$$$\  
 * $$  __$$\ \_$$  _|$$  __$$\ $$ |      $$ |     $$  __$$\ 
 * $$ /  \__|  $$ |  $$ /  $$ |$$ |      $$ |     $$ /  $$ |
 * $$ |        $$ |  $$$$$$$$ |$$ |      $$ |     $$ |  $$ |
 * $$ |        $$ |  $$  __$$ |$$ |      $$ |     $$ |  $$ |
 * $$ |  $$\   $$ |  $$ |  $$ |$$ |      $$ |     $$ |  $$ |
 *  $$$$$$ | $$$$$$\ $$ |  $$ |$$$$$$$$\ $$$$$$$$\ $$$$$$  |
 * \______/  \______|\__|  \__|\________|\________|\______/ 
 *
 * Author:  Nanako7_ix
 * Created: 2025/05/22 16:27:34
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

constexpr i64 INF = 1E9;

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<array<int, 2>>> adj(n + 1);
    for (int i = 1; i <= m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    vector<array<i64, 32>> dp(n + 1);
    for (int i = 1; i <= n; ++i) {
        dp[i][1] = 1;
    }

    for (int k = 2; k <= 31; ++k) {
        for (int u = 1; u <= n; ++u) {
            for (auto [v, w] : adj[u]) {
                dp[u][k] = max(dp[u][k], dp[v][k - 1] * w);
            }
            dp[u][k] = min(dp[u][k], INF + 1);
        }
    }

    for (int i = 1; i <= q; ++i) {
        int u, x;
        cin >> u >> x;
        for (int j = 1; j <= 31; ++j) {
            if (dp[u][j] > x) {
                cout << j - 1 << endl;
                break;
            }
        }
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