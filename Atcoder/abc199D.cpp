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
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    i64 ans = 1;
    vector<int> vis(n + 1);
    vector<array<int, 3>> cnt(n + 1, array<int, 3> {});
    for (int i = 1; i <= n; ++i) {
        if (vis[i]) continue;
        vector<int> p;
        auto dfs = [&](auto dfs, int u) -> void {
            vis[u] = 1;
            p.push_back(u);
            for (auto v : adj[u]) {
                if (vis[v] == 0) {
                    dfs(dfs, v);
                }
            }
        };
        dfs(dfs, i);

        i64 res = 0;
        auto jxt = [&](auto jxt, int u) -> void {
            if (u == (int) p.size()) {
                res += 3;
                return;
            }
            int cur = p[u];
            for (int i = 0; i < 3; ++i) {
                if (cnt[cur][i]) continue;
                for (auto v : adj[cur]) {
                    cnt[v][i]++;
                }
                jxt(jxt, u + 1);
                for (auto v : adj[cur]) {
                    cnt[v][i]--;
                }
            }
        };
    
        for (auto x : adj[p[0]]) {
            cnt[x][0] = 1;
        }
        jxt(jxt, 1);
        ans *= res;
    }
    cout << ans << "\n";
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