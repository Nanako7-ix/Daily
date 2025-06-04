/**
 * Author: Nanako7_ix
 * Created: 2025/04/15 22:47:02
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

struct BlockCutTree {
    int n, cur;
    vector<vector<int>> adj, tr;
    vector<int> dfn, low, stk;

    BlockCutTree (int n = 0) {
        init(n);
    }

    void init(int n) {
        this -> n = n;
        cur = 0;
        adj.assign(n + 1, {});
        tr.assign(n + 1, {});
        dfn.assign(n + 1, 0);
        low.assign(n + 1, 0);
        stk.clear();
    }

    void add(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int u, int fa) {
        int child = 0;
        stk.push_back(u);
        low[u] = dfn[u] = ++cur;
        for (auto v : adj[u]) {
            if (!dfn[v]) {
                child++;
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                if(low[v] >= dfn[u]) {
                    vector<int> vdcc {u};
                    int x;
                    do {
                        x = stk.back();
                        stk.pop_back();
                        vdcc.push_back(x);
                    } while(x != v);

                    for(auto x : vdcc) {
                        tr[x].push_back(tr.size());
                    }

                    tr.push_back(vdcc);
                }
            } else if (v != fa) {
                low[u] = min(low[u], dfn[v]);
            }
        }

        if (fa == 0 && child == 0) {
            tr[u].push_back(tr.size());
            tr.push_back({u});
        }
    }

    void work() {
        for (int i = 1; i <= n; ++i) {
            if (!dfn[i]) dfs(i, 0);
        }
    }

    vector<vector<int>> vdcc() {
        return vector (tr.begin() + n, tr.end());
    }
};

struct LCA {
    int n, tot;
    vector<vector<int>> adj, st;
    vector<int> fa, dep, dfn, siz;
    LCA() = default;
    LCA(int n) { init(n); }
    void init(int n) {
        this -> n = n;
        tot = 0;
        adj.assign(n + 1, {});
        st.assign(__lg(n) + 1, vector<int> (n + 1));
        fa.assign(n + 1, 0);
        dep.assign(n + 1, 0);
        dfn.assign(n + 1, 0);
        siz.assign(n + 1, 0);
    }
    void add(int u, int v) {
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    void dfs(int u) {
        if(fa[u] != 0) adj[u].erase(find(adj[u].begin(), adj[u].end(), fa[u]));
        siz[u] = 1;
        st[0][dfn[u] = ++tot] = u;
        for(auto v : adj[u]) {
            dep[v] = dep[fa[v] = u] + 1;
            dfs(v);
            siz[u] += siz[v];
        }
    }
    int merge(int x, int y) {
        return dep[x] < dep[y] ? x : y;
    }
    void work(int rt = 1) {
        dep[rt] = 1;
        dfs(rt);
        for(int i = 1; i <= __lg(n); ++i) {
            for(int j = 1; j + (1 << i) - 1 <= n; ++j) {
                st[i][j] = merge(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
            }
        }
    }
    int operator()(int u, int v) {
        if(u == v) return u;
        u = dfn[u], v = dfn[v];
        if(u > v) swap(u,  v);
        int len = __lg(v - u);
        return fa[merge(st[len][u + 1], st[len][v - (1 << len) + 1])];
    }
    bool isAncester(int f, int u) {
        return operator()(f, u) == f;
    }
    int rootedParent(int rt, int u) {
        if(rt == u) return rt;
        if (!isAncester(u, rt)) return fa[u];
        auto it = upper_bound(adj[u].begin(), adj[u].end(), rt, [&](int x, int y) {
            return dfn[x] < dfn[y];
        }) - 1;
        return *it;
    }
    int rootedSize(int rt, int u) {
        if (rt == u) return n;
        if (!isAncester(u, rt)) return siz[u];
        return n - siz[rootedParent(rt, u)];
    }
    int rootedLca(int rt, int u, int v) {
        return operator()(rt, u) ^ operator()(u, v) ^ operator()(v, rt);
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    BlockCutTree tr(n);
    for(int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        tr.add(u, v);
    }
    tr.work();
    auto adj = tr.tr;

    LCA lca(adj.size() - 1);
    for(int u = 1; u <= n; ++u) {
        for(auto v : adj[u]) {
            lca.add(u, v);
        }
    }
    lca.work();

    int q; cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        int w = lca(u, v);
        u = lca.dep[u];
        v = lca.dep[v];
        w = lca.dep[w];
        int dis = u + v - 2 * w;
        cout << dis / 2 + 1 << endl;
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