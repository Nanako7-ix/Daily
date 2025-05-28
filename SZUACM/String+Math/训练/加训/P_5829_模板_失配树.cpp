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
 * Created: 2025/05/21 20:29:41
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
    string s;
    cin >> s;
    int n = s.size();

    LCA lca(n + 1);
    vector<int> fail(n);
    for (int i = 1, j = 0; i < n; ++i) {
        while (j && s[i] != s[j]) j = fail[j - 1];
        fail[i] = j += s[i] == s[j];
        lca.add(i + 2, fail[i] + 1);
    }
    lca.add(1, 2);
    lca.work();

    int q; cin >> q;
    for (int i = 1; i <= q; ++i) {
        int u, v;
        cin >> u >> v;
        int w = lca(u + 1, v + 1) - 1;
        if (w == u || w == v) {
            w = fail[w - 1];
        }
        cout << w << endl;
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