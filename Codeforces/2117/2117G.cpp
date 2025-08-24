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
 * Created: 2025/06/19 16:22:24
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
using f64 = double;

constexpr int inf = 0x3f3f3f3f;
constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;

struct DSU {
    int n, cnt;
    std::vector<int> f, siz;

    DSU() = default;

    DSU(int n) { init(n); }

    void init(int n) {
        this -> n = n;
        cnt = n;
        f.resize(n + 1);
        siz.assign(n + 1, 1);
        std::iota(f.begin(), f.end(), 0);
    }

    int find(int x) {
        if(f[x] == x) return x;
        return f[x] = find(f[x]);
    }

    bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        cnt--;
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    int size(int x) {
        return siz[find(x)];
    }

    int count() const {
        return cnt;
    }
};

struct HLD {
    int n = 0, tot = 0;
    std::vector<std::vector<int>> adj;
    std::vector<int> dfn, idfn, siz, fa, top, dep;
    HLD() = default;
    HLD(int n) { init(n); }
    void init(int n) {
        this -> n = n;
        tot = 0;
        adj.assign(n + 1, {});
        dfn .assign(n + 1, 0);
        idfn.assign(n + 1, 0);
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
                std::swap(v, adj[u][0]);
            }
        }
    }
    void dfs2(int u) {
        dfn[u] = ++tot;
        idfn[tot] = u;
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
    int jump(int u, int k) {
        assert(dep[u] >= k);
        int d = dep[u] - k;
        while(dep[top[u]] > d) {
            u = fa[top[u]];
        }
        return idfn[dfn[u] - dep[u] + d];
    }
    template<typename Func>
    void modify(int u, int v, Func modify) {
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
    template<typename Func>
    void modify(int u, Func modify) {
        modify(dfn[u], dfn[u] + siz[u] - 1);
    }
    template<typename Func, typename T = std::invoke_result_t<Func, int, int>>
    T query(int u, int v, Func query) {
        T res {};
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
    template<typename Func, typename T = std::invoke_result_t<Func, int, int>>
    T query(int u, Func query) {
        return query(dfn[u], dfn[u] + siz[u] - 1);
    }
    bool isAncester(int f, int u) {
        return dfn[f] <= dfn[u] && dfn[u] < dfn[f] + siz[f];
    }
    int rootedParent(int rt, int u) {
        if(rt == u) return rt;
        if (!isAncester(u, rt)) return fa[u];
        auto it = std::upper_bound(adj[u].begin(), adj[u].end(), rt, [&](int x, int y) {
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

template<typename T, typename Func>
class SparseTable {
private:
    int n;
    Func op;
    std::vector<std::vector<T>> st;
public:
    SparseTable () = default;

    template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
    SparseTable (const Iterator& l, const Iterator& r, Func&& f) : op(f) {
        init(l, r);
    }

    template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
    void init (const Iterator& l, const Iterator& r) {
        n = r - l;
        st.assign(std::__lg(n) + 1, std::vector<T> (n + 1));
        for (int i = 1; i <= n; ++i) {
            st[0][i] = *(l + i - 1);
        }
        for (int i = 1; i <= std::__lg(n); ++i) {
            for (int j = 1; j + (1 << i) - 1 <= n; ++j) {
                st[i][j] = op(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    T operator () (int l, int r) {
        assert(l <= r);
        int k = std::__lg(r - l + 1);
        return op(st[k][l], st[k][r - (1 << k) + 1]);
    }

    T query (int l, int r) {
        T res {};  
        int len = r - l + 1;
        for (int i = 0, k = l; i <= std::__lg(len); ++i) {
            if(len >> i & 1) {
                res = k == l ? st[i][l] : op(res, st[i][k]);
                k += 1 << i;
            }
        }
        return res;
    }
};

template<typename Iterator, typename Func>
SparseTable (const Iterator&, const Iterator&, Func&&) ->
SparseTable<typename std::iterator_traits<Iterator>::value_type, Func>;

struct Info {
    i64 Min, Max;
    Info (i64 x = INF, i64 y = 0) {
        this -> Min = x;
        this -> Max = y;
    }
};

Info operator+(const Info& x, const Info& y) {
    return Info { min(x.Min, y.Min), max(x.Max, y.Max) };
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<array<i64, 3>> edges(m + 1);
    for (int i = 1; i <= m; ++i) {
        auto& [u, v, w] = edges[i];
        cin >> u >> v >> w;
    }
    sort(edges.begin() + 1, edges.end(), [](array<i64, 3> x, array<i64, 3> y) {
        return x[2] < y[2];
    });

    vector<vector<array<i64, 2>>> adj(n + 1);
    DSU dsu(n);
    HLD hld(n);
    for (int i = 1; i <= m; ++i) {
        auto [u, v, w] = edges[i];
        if (dsu.merge(u, v)) {
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
            hld.add(u, v);
        }
    }
    hld.work(1);

    vector<Info> a(n + 1);
    [&](this auto&& dfs, int u, int fa) -> void {
        for (auto [v, w] : adj[u]) {
            if (v == fa) continue;
            a[hld.dfn[v]] = Info { w,w };
            dfs(v, u);
        }
    } (1, 0);

    SparseTable MinMax(a.begin() + 1, a.end(), plus<Info> {});
    
    i64 ans = INF;
    for (int i = 1; i <= n; ++i) {
        Info x = hld.query(1, i, [&](int l, int r) {
            return MinMax(l, r);
        });
        Info y = hld.query(1, n, [&](int l, int r) {
            return MinMax(l, r);
        });
        Info z = hld.query(i, n, [&](int l, int r) {
            return MinMax(l, r);
        });
        auto [Min, Max] = x + y + z;
        ans = min(ans, Min + Max);
    }
    cout << ans << "\n";
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T = 1;
    cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}