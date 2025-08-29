#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

void Thephix() {
    int n, k;
    cin >> n >> k;
    vector<i64> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector dp(n + 1, vector<array<i64, 3>> (k + 1));
    auto dfs = [&](auto &&dfs, int u, int fa) -> void {
        vector<vector<i64>> dis(k + 1);
        for (auto v : adj[u]) {
            if (v == fa) continue;
            dfs(dfs, v, u);
            for (int i = 0; i <= k; ++i) {
                for (int j = 0; j <= k; ++j) {
                    if (i + j > k) continue;
                    dp[u][i + j][0] = max(
                        dp[u][i + j][0],
                        dp[u][i][0] + max(dp[v][j][0], dp[v][j][2])
                    );
                    dp[u][i + j][1] = max(
                        dp[u][i + j][0],
                        dp[u][i][0] + dp[v][j][0]
                    );
                }
                dis[i].push_back(dp[v][i][1] - dp[v][i][0]);
            }
        }

        for (int i = 1; i <= k; ++i) {
            sort(dis[i].begin(), dis[i].end(), greater<i64> {});
            if (dis[i].size() >= 2) {
                dp[u][i][2] = dp[u][i][1];
                dp[u][i][2] += a[u] + dis[i][0] + dis[i][1];
            }

            if (dis[i].size() != 0) {
                dp[u][i][1] += dis[i][0];
                dp[u][i][1] += a[u];
            } else {
                dp[u][i][1] += a[u];
            }
        }

        cout << u << ": " << "\n";
        for (int i = 0; i <= k; ++i) {
            cout << dp[u][i][0] << ' ' << dp[u][i][1] << ' ' << dp[u][i][2] << "\n";
        }
    };

    dfs(dfs, 1, 0);
    cout << *max_element(dp[1][k].begin(), dp[1][k].end()) << "\n";
}

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T = 1;
    // cin >> T;

    while (T--) {
        Thephix();
    }

    return 0;
}