#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

int main () {
    int n;
    cin >> n;
    vector<vector<array<int, 2>>> adj(n + 1);
    for (int i = 1; i < n; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    vector<i64> dp(n + 1), dep(n + 1);
    [&](this auto&& dfs, int u, int fa) -> void {
        for (auto [v, w] : adj[u]) {
            if (v == fa) continue;
            dp[v] = w - dp[u];
            dep[v] = dep[u] + 1;
            dfs(v, u);
        }
    } (1, 0);

    i64 l = -1E18, r = 1E18;
    for (int u = 1; u <= n; ++u) {
        if (dep[u] % 2 == 1) {
            l = max(l, dp[u] - (i64) 1E9);
            r = min(r, dp[u] - 1);
        } else {
            l = max(l, 1 - dp[u]);
            r = min(r, (i64) 1E9 - dp[u]);
        }
    }

    if (l > r) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        for (int i = 1; i <= n; ++i) {
            cout << (dep[i] % 2 == 1 ? dp[i] - l : dp[i] + l) << " \n"[i == n];
        }
    }
}