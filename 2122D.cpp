#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr i64 inf = 1E9;

void Thephix() {
    int n, m;
    cin >> n >> m;
    vector<int> deg(n + 1);
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        deg[u]++, deg[v]++;
    }

    vector<int> dp(n + 1, inf);
    dp[1] = 0;
    for (int t = 0; true; ++t) {
        vector<int> ndp(n + 1, inf);
        for (int u = 1; u <= n; ++u) {
            if (dp[u] == inf) continue;
            int v = adj[u][t % deg[u]];
            ndp[u] = min(ndp[u], dp[u] + 1);
            ndp[v] = min(ndp[v], dp[u]);
        }
        if (ndp[n] != inf) {
            cout << t + 1 << ' ' << ndp[n] << "\n";
            return;
        }
        swap(dp, ndp);
    }
}

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T = 1;
    cin >> T;

    while (T--) {
        Thephix();
    }

    return 0;
}