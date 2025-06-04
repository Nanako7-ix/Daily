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
 * Created: 2025/05/16 20:38:45
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
    int n, m, rt;
    cin >> n >> m >> rt;
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> dep(n + 1);
    vector fa(n + 1, vector<int> (__lg(n) + 1));
    
    auto dfs = [&](auto&& dfs, int u) -> void {
        for (auto v : adj[u]) {
            if (v == fa[u][0]) continue;
            fa[v][0] = u;
            dep[v] = dep[u] + 1;
            dfs(dfs, v);
        }
    };

    dfs(dfs, rt);
    for (int i = 1; i <= __lg(n); ++i) {
        for (int u = 1; u <= n; ++u) {
            fa[u][i] = fa[fa[u][i - 1]][i - 1];
        }
    }

    auto lca = [&](int u, int v) -> int {
        while (dep[u] != dep[v]) {
            if (dep[u] < dep[v]) swap(u, v);
            u = fa[u][__lg(dep[u] - dep[v])];
        }
        if (u == v) return u;
        for (int i = __lg(dep[u]); i >= 0; --i) {
            if (fa[u][i] != fa[v][i]) {
                u = fa[u][i], v = fa[v][i];
            }
        }
        return fa[u][0];
    };

    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        cout << lca(u, v) << endl;
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