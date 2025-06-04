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
 * Created: 2025/05/17 21:09:06
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

struct HLD {
    int n = 0, tot = 0;
    vector<vector<int>> adj;
    vector<int> dfn, rnk, siz, fa, top, dep;
    HLD() = default;
    HLD(int n) { init(n); }
    void init(int n) {
        this -> n = n;
        tot = 0;
        adj.assign(n + 1, {});
        dfn .assign(n + 1, 0);
        rnk.assign(n + 1, 0);
        siz.assign(n + 1, 0);
        fa .assign(n + 1, 0);
        top.assign(n + 1, 0);
        dep.assign(n + 1, 0);
    }
    void add(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void work(int root = 1) {
        dfs1(root);
        dfs2(root);
    }
    void dfs1(int u) {
        if(fa[u] != 0) {
            adj[u].erase(find(adj[u].begin(), adj[u].end(), fa[u]));
        }

        siz[u] = 1;
        for(auto& v : adj[u]) {
            dep[v] = dep[fa[v] = u] + 1;
            dfs1(v);
            siz[u] += siz[v];
            if(siz[v] > siz[adj[u][0]]) {
                swap(v, adj[u][0]);
            }
        }
    }
    void dfs2(int u) {
        dfn[u] = ++tot;
        rnk[tot] = u;
        for (auto v : adj[u]) {
            top[v] = v == adj[u][0] ? top[u] : v;
            dfs2(v);
        }
    }
    int lca(int u, int v) {
        while(top[u] != top[v]) {
            if(dep[top[u]] > dep[top[v]]) {
                u = fa[top[u]];
            } else {
                v = fa[top[v]];
            }
        }
        return dep[u] < dep[v] ? u : v;
    }
    int jmp(int u, int k) {
        assert(dep[u] >= k);
        int d = dep[u] - k;
        while(dep[top[u]] > d) {
            u = fa[top[u]];
        }
        return rnk[dfn[u] - dep[u] + d];
    }
    void modify(int u, int v, auto modify) {
        while(top[u] != top[v]) {
            if(dep[top[u]] > dep[top[v]]) {
                modify(dfn[top[u]], dfn[u]);
                u = fa[top[u]];
            } else {
                modify(dfn[top[v]], dfn[v]);
                v = fa[top[v]];
            }
        }
        if(dep[u] < dep[v]) {
            modify(dfn[u], dfn[v]);
        } else modify(dfn[v], dfn[u]);
    }
    void modify(int u, auto modify) {
        modify(dfn[u], dfn[u] + siz[u] - 1);
    }
    template<typename T>
    T query(int u, int v, auto query) {
        T res{};
        while(top[u] != top[v]) {
            if(dep[top[u]] > dep[top[v]]) {
                res = res + query(dfn[top[u]], dfn[u]);
                u = fa[top[u]];
            } else {
                res = res + query(dfn[top[v]], dfn[v]);
                v = fa[top[v]];
            }
        }
        if(dep[u] < dep[v]) {
            res = res + query(dfn[u], dfn[v]);
        } else res = res + query(dfn[v], dfn[u]);
        return res;
    }
    template<typename T>
    T query(int u, auto query) {
        return query(dfn[u], dfn[u] + siz[u] - 1);
    }
    bool isAncester(int f, int u) {
        return dfn[f] <= dfn[u] && dfn[u] < dfn[f] + siz[f];
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
        return lca(rt, u) ^ lca(u, v) ^ lca(v, rt);
    }
};

template<typename Info>
struct Fenwick {
    int n;
    std::vector<Info> tr;

    Fenwick () = default;
    Fenwick (int n, Info e = {}) { init(n, e); }

    template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
    Fenwick (const Iterator& l, const Iterator& r) { init(l, r); }

    void init (int n, Info e = {}) {
        vector<Info> _(n, e);
        init(_.begin(), _.end());
    }

    template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
    void init (const Iterator& l, const Iterator& r) {
        n = r - l;
        tr.assign(n + 1, Info {});
        for(int i = 1; i <= n; ++i) {
            tr[i] += *(l + i - 1);
            if(i + (i & -i) <= n) {
                tr[i + (i & -i)] += tr[i];
            }
        }
    }

    void add (int p, const Info& v) {
        for(; p <= n; p += p & -p) tr[p] += v;
    }

    Info query (int p, Info res = {}) {
        assert(p >= 0);
        for(; p; p -= p & -p) res += tr[p];
        return res;
    }

    Info query (int l, int r) {
        assert(l <= r && l != 0);
        return query(r) - query(l - 1);
    }

    int lower_bound (Info k) {
        int x = 0;
        for(int i = 1 << std::__lg(n); i; i >>= 1)
            if(x + i <= n && tr[x + i] < k)
                k -= tr[x += i];
        return x + 1;
    }

    int upper_bound (Info k) {
        int x = 0;
        for(int i = 1 << std::__lg(n); i; i >>= 1)
            if(x + i <= n && tr[x + i] <= k)
                k -= tr[x += i];
        return x + 1;
    }
};

void solve() {
    int n;
    cin >> n;
    vector<array<int, 2>> edges(n);
    HLD hld(n);
    for (int i = 1; i < n; ++i) {
        auto& [u, v] = edges[i];
        cin >> u >> v;
        hld.add(u, v);
    }

    hld.work(1);
    i64 sum = n;
    Fenwick<i64> tr(n);
    for (int i = 1; i <= n; ++i) {
        tr.add(hld.dfn[i], 1);
    }

    int q; cin >> q;
    for (int i = 1; i <= q; ++i) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, w;
            cin >> x >> w;
            tr.add(hld.dfn[x], w);
            sum += w;
        } else {
            int x; cin >> x;
            auto [u, v] = edges[x];
            if (hld.dep[u] > hld.dep[v]) {
                swap(u, v);
            }
            cout << abs(sum - 2 * hld.query<i64>(v, [&](int l, int r) {
                return tr.query(l, r);
            })) << endl;
        }
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