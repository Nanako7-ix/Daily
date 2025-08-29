#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
using i64 = long long;

constexpr int inf = 1E9;
constexpr i64 Mod = 998244353;

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<array<int, 2>> E(n);
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; ++i) {
        auto& [u, v] = E[i];
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> dep(n + 1);
    vector fa(n + 1, vector<array<int, 2>>(__lg(n) + 1));

    auto dfs = [&](auto&& dfs, int u) -> void {
        for (auto& v : adj[u]) {
            if (v == fa[u][0][0]) continue;
            fa[v][0][0] = u;
            dep[v] = dep[u] + 1;
            dfs(dfs, v);
        }
    };
    dfs(dfs, 1);


    for (int i = 0; i < m; ++i) {
        int p; cin >> p;
        auto [u, v] = E[p];
        if (fa[u][0][0] != v) {
            swap(u, v);
        }
        fa[u][0] = { v, 1 << i };
    }
    for (int i = 1; i <= __lg(n); ++i) {
        for (int u = 1; u <= n; ++u) {
            fa[u][i][0] = fa[fa[u][i - 1][0]][i - 1][0];
            fa[u][i][1] = fa[u][i - 1][1] | fa[fa[u][i - 1][0]][i - 1][1];
        }
    }

    auto lca = [&](int u, int v) -> int {
        int res = 0;
        if (dep[u] < dep[v]) swap(u, v);
        while (dep[u] > dep[v]) {
            res |= fa[u][__lg(dep[u] - dep[v])][1];
            u = fa[u][__lg(dep[u] - dep[v])][0];
        }
        if (u == v) return res;
        for (int i = __lg(dep[u]); i >= 0; --i) {
            if (fa[u][i][0] == fa[v][i][0]) continue;
            res |= fa[u][i][1], u = fa[u][i][0];
            res |= fa[v][i][1], v = fa[v][i][0];
        }
        return res | fa[u][0][1] | fa[v][0][1];
    };

    vector<int> cnt(1 << m);
    for (int i = 1; i <= k; ++i) {
        int u, v;
        cin >> u >> v;
        cnt[lca(u, v)]++;
    }

    vector<array<i64, 2>> dp(1 << m, { inf, 0 });
    dp[0] = { 0, 1 };
    for (int t = 1; t < (1 << m); ++t) {
        if (cnt[t] == 0) continue;
        for (int s = (1 << (__lg(t) + 1)) - 1; s >= 0; --s) {
            if ((s | t) == s || dp[s][0] == inf) continue;
            auto [len, ans] = dp[s];
            len += 1;
            (ans *= cnt[t]) %= Mod;
            if (dp[s | t][0] == len) {
                dp[s | t][1] += ans;
                dp[s | t][1] %= Mod;
            } else if (dp[s | t][0] > len) {
                dp[s | t] = { len, ans };
            }
        }
    }

    auto [len, ans] = dp[(1 << m) - 1];
    if (len == inf) {
        cout << "-1\n";
    } else {
        cout << len << ' ' << ans << "\n";
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(0);
    solve();
    return 0;
}