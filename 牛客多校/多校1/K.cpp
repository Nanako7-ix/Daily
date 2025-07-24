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
    int n;
    cin >> n;
    vector<array<int, 4>> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i][0];
        for (int j = 1; j <= a[i][0]; ++j) {
            cin >> a[i][j];
        }
    }

    vector<array<int, 4>> deg(n + 1);
    vector<array<array<int, 2>, 4>> nxt(n + 1);
    vector<array<vector<array<int, 2>>, 4>> adj(n + 1);
    for (int u = 1; u <= n; ++u) {
        for (int p = 1; p <= a[u][0]; ++p) {
            int v = a[u][p];
            for (int i = 1; i <= a[v][0]; ++i) {
                if (a[v][i] == u) {
                    nxt[u][p] = { v, i % a[v][0] + 1 };
                    deg[v][i % a[v][0] + 1]++;
                    adj[v][i % a[v][0] + 1].push_back({ u, p });
                    break;
                }
            }
        }
    }

    queue<array<int, 2>> q;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= a[i][0]; ++j) {
            if (deg[i][j] == 0) {
                q.push(array {i, j});
            }
        }
    }
    while (!q.empty()) {
        auto [u, p] = q.front();
        q.pop();
        auto [v, x] = nxt[u][p];
        if (--deg[v][x] == 0) {
            q.push(nxt[u][p]);
        }
    }

    vector<array<int, 4>> ans(n + 1);
    vector<array<int, 4>> vis(n + 1);
    for (int u = 1; u <= n; ++u) {
        for (int p = 1; p <= a[u][0]; ++p) {
            if (vis[u][p] || deg[u][p] == 0) continue;
            vector<array<int, 2>> cir;
            map<array<int, 2>, int> cnt;
            for (array x = {u, p}; !vis[x[0]][x[1]]; x = nxt[x[0]][x[1]]) {
                cir.push_back(x);
                vis[x[0]][x[1]] = 1;
                cnt[{
                    min(x[0], nxt[x[0]][x[1]][0]),
                    max(x[0], nxt[x[0]][x[1]][0])
                }]++;
            }

            auto dfs = [&](auto&& dfs, array<int, 2> u, array<int, 2> fa) -> void {
                ans[u[0]][u[1]] = cnt.size();
                for (auto v : adj[u[0]][u[1]]) {
                    if (v == fa || deg[v[0]][v[1]]) {
                        continue;
                    }
                    cnt[{ min(u[0], v[0]), max(u[0], v[0]) }]++;
                    dfs(dfs, v, u);
                    if (--cnt[{ min(u[0], v[0]), max(u[0], v[0]) }] == 0) {
                        cnt.erase({ min(u[0], v[0]), max(u[0], v[0]) });
                    }
                }
            };

            for (auto u : cir) {
                dfs(dfs, u, u);
            }
        }
        cout << ans[u][1] << "\n";
    }
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T = 1;
    // cin >> T;

    while (T--) {
        Thephix();
    }

    return 0;
}