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
    int n, m, x, y;
    cin >> n >> m >> x >> y;
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int ok = 0;
    vector<int> ans, vis(n + 1);
    auto dfs = [&](auto&& dfs, int u) -> void {
        ans.push_back(u);
        vis[u] = 1;
        if (u == y) {
            for (auto x : ans) {
                cout << x << ' ';
            }
            cout << "\n";
            ok = 1;
            return;
        }
        sort(adj[u].begin(), adj[u].end());
        for (auto v : adj[u]) {
            if (vis[v]) continue;
            dfs(dfs, v);
            if (ok) return;
        }
        ans.pop_back();
    };

    dfs(dfs, x);
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