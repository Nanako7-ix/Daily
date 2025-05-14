/**
 * Author:  Nanako7_ix
 * Created: 2025/05/12 22:28:56
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

struct EBCC {
    int n;
    vector<vector<array<int, 2>>> adj;
    vector<array<int, 2>> bridge;
    vector<int> stk;
    vector<int> dfn, low, bel;
    int cur, cnt, edges;

    EBCC () = default;
    EBCC (int n) {
        init(n);
    }

    void init (int n) {
        this -> n = n;
        adj.assign(n + 1, {});
        dfn.assign(n + 1, 0);
        low.assign(n + 1, 0);
        bel.assign(n + 1, 0);
        stk.clear();
        cur = cnt = edges = 0;
    }

    void add (int u, int v) {
        adj[u].push_back({v, edges++});
        adj[v].push_back({u, edges++});
    }

    void tarjan (int u, int fa) {
        dfn[u] = low[u] = ++cur;
        stk.push_back(u);
        for (auto [v, id] : adj[u]) {
            if ((id ^ fa) == 1) continue;
            if (dfn[v] == 0) {
                tarjan(v, id);
                low[u] = min(low[u], low[v]);
                if (dfn[u] > low[v]) {
                    bridge.push_back({u, v});
                }
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (low[u] == dfn[u]) {
            int x = ++cnt;
            do {
                bel[x = stk.back()] = cnt;
                stk.pop_back();
            } while (x != u);
        }
    }

    vector<int> work() {
        tarjan(1, -1);
        return bel;
    }

    struct Graph {
        int n;
        vector<vector<int>> adj;
    };

    Graph getTree() {
        work();
        Graph g;
        g.n = *max_element(bel.begin() + 1, bel.end());
        for (auto [u, v] : bridge) {
            g.adj[bel[u]].push_back(bel[v]);
            g.adj[bel[v]].push_back(bel[u]);
        }
        return g;
    }
};

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(k + 1), c(n + 1);
    for (int i = 1; i <= k; ++i) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> c[i];
    }
    
    EBCC ebcc(n);
    vector<array<int, 3>> edges(m + 1);
    for (int i = 1; i <= m; ++i) {
        cin >> edges[i][2];
    }
    for (int i = 1; i <= m; ++i) {
        cin >> edges[i][0] >> edges[i][1];
        ebcc.add(edges[i][0], edges[i][1]);
    }

    auto bel = ebcc.work();
    int tn = ebcc.cnt;
    vector<vector<array<i64, 2>>> adj(tn + 1);
    for (int i = 1; i <= m; ++i) {
        auto [u, v, w] = edges[i];
        if (bel[u] == bel[v]) continue;
        adj[bel[u]].push_back({bel[v], w});
        adj[bel[v]].push_back({bel[u], w});
    }
    
    vector<i64> dp(tn + 1), cnt(tn + 1);
    for (int i = 1; i <= n; ++i) {
        dp[bel[i]] += c[i];
    }
    for (int i = 1; i <= k; ++i) {
        cnt[bel[a[i]]]++;
    }
    auto dfs1 = [&](auto &&dfs, int u, int fa) -> void {
        for (auto [v, w] : adj[u]) {
            if (v == fa) continue;
            dfs(dfs, v, u);
            if (cnt[v] == 0 || cnt[v] == k) {
                w = 0;
            }
            dp[u] += max(0LL, dp[v] - w);
            cnt[u] += cnt[v];
        }
    };
    auto dfs2 = [&](auto &&dfs, int u, int fa) -> void {
        for (auto [v, w] : adj[u]) {
            if (v == fa) continue;
            if (cnt[v] == 0 || cnt[v] == k) {
                w = 0;
            }
            i64 get = dp[u] - max(0LL, dp[v] - w);
            dp[v] += max(0LL, get - w);
            dfs(dfs, v, u);
        }
    };
    dfs1(dfs1, 1, 0);
    dfs2(dfs2, 1, 0);

    for (int i = 1; i <= n; ++i) {
        cout << dp[bel[i]] << " \n"[i == n];
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