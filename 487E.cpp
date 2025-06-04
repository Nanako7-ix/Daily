/**
 * Author: Nanako7_ix
 * Created: 2025/04/13 22:41:32
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
    vector<vector<int>> adj, vdcc;
    vector<int> dfn, low, stk;

    vector<int> cut;

    BlockCutTree (int n = 0) {
        init(n);
    }

    void init(int n) {
        this -> n = n;
        cur = 0;
        adj.assign(n + 1, {});
        dfn.assign(n + 1, 0);
        low.assign(n + 1, 0);
        cut.assign(n + 1, 0);
        vdcc.clear();
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
                    if (fa == 0) {
                        cut[u] = 1;
                    }
                    vector<int> component {u};
                    int x;
                    do {
                        x = stk.back();
                        stk.pop_back();
                        component.push_back(x);
                    } while(x != v);

                    vdcc.push_back(component);
                }
            } else if (v != fa) {
                low[u] = min(low[u], dfn[v]);
            }
        }

        if (fa == 0 && child == 0) {
            vdcc[u].push_back(vdcc.size());
            vdcc.push_back({u});
        }

        if (fa == 0 && child >= 2) {
            cut[u] = 1;
        }
    }

    void work() {
        for (int i = 1; i <= n; ++i) {
            if (!dfn[i]) dfs(i, 0);
        }
    }

    struct Graph {
        int n, m;
        vector<vector<int>> adj;
    };
    
    Graph getTree() {
        work();
        Graph G;
        G.n = n, G.m = vdcc.size();
        G.adj.assign(G.n + G.m + 1, {});
        for (int i = 1; i <= G.m; ++i) {
            for (auto x : vdcc[i - 1]) {
                G.adj[x].push_back(i + G.n);
                G.adj[i + G.n].push_back(x);
            }
        }
        return G;
    }
};

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

#define ls(u) (u << 1)
#define rs(u) (u << 1 | 1)
template<typename Info>
struct SegmentTree {
    constexpr static int inf = 0x3f3f3f3f;
    using i64 = long long;
    int n;
    std::vector<Info> info;

    SegmentTree() = default;

    SegmentTree(int n, Info e = {}) { init(n, e); }

    template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
    SegmentTree(const Iterator& l, const Iterator& r) { init(l, r); }

    void init(int n, Info e = {}) {
        vector<Info> _(n, e);
        init(_.begin(), _.end());
    }

    template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
    void init(const Iterator& l, const Iterator& r) {
        n = r - l;
        info.assign(4 << std::__lg(n), Info {});
        build(1, 1, n, l);
    }

    void pull(int u) {
        info[u] = info[ls(u)] + info[rs(u)];
    }

    template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
    void build(int u, int l, int r, const Iterator& it) {
        if (l == r) {
            info[u] = {*it};
            return;
        }
        int m = (l + r) >> 1;
        build(ls(u), l, m, it);
        build(rs(u), m + 1, r, it + (m - l + 1));
        pull(u);
    }

    template<typename Func>
    void modify(int p, Func&& op, int u, int l, int r) {
        if (l == r) {
            op(info[u]);
            return;
        }
        int m = (l + r) >> 1;
        if (p <= m) {
            modify(p, op, ls(u), l, m);
        } else {
            modify(p, op, rs(u), m + 1, r);
        }
        pull(u);
    }

    template<typename Func>
    void modify(int p, Func&& op) {
        modify(p, op, 1, 1, n);
    }

    Info query(int L, int R, int u, int l, int r) {
        if (L <= l && r <= R) {
            return info[u];
        }
        int m = (l + r) >> 1;
        if (R <= m) {
            return query(L, R, ls(u), l, m);
        } else if (L > m) {
            return query(L, R, rs(u), m + 1, r);
        } else {
            return query(L, R, ls(u), l, m) + query(L, R, rs(u), m + 1, r);
        }
    }

    Info query(int l, int r) {
        assert(l <= r);
        return query(l, r, 1, 1, n);
    }

    int kth(i64 k, int u, int l, int r) {
        assert(info[u].size() >= k);
        if(l == r) return l;
        int m = (l + r) >> 1;
        if(info[ls(u)].size() >= k) {
            return kth(k, ls(u), l, m);
        } else {
            return kth(k - info[ls(u)].size(), rs(u), m + 1, r);
        }
    }

    int kth(i64 k) {
        assert(info[1].size() >= k);
        return kth(k, 1, 1, n);
    }

    template<typename Func>
    int FindFirst(int L, int R, Func&& f, int u, int l, int r) {
        if(l > R || r < L || !f(info[u])) return inf;
        if(l == r) return l;
        int m = (l + r) >> 1;
        int res = FindFirst(L, R, f, ls(u), l, m);
        if(res == inf) {
            res = FindFirst(L, R, f, rs(u), m + 1, r);
        }
        return res;
    }

    template<typename Func>
    int FindFirst(int l, int r, Func&& f) {
        assert(l <= r);
        return FindFirst(l, r, f, 1, 1, n);
    }

    template<typename Func>
    int FindLast(int L, int R, Func&& f, int u, int l, int r) {
        if(l > R || r < L || !f(info[u])) return -inf;
        if(l == r) return l;
        int m = (l + r) >> 1;
        int res = FindLast(L, R, f, rs(u), m + 1, r);
        if(res == -inf) {
            res = FindLast(L, R, f, ls(u), l, m);
        }
        return res;
    }

    template<typename Func>
    int FindLast(int l, int r, Func&& f) {
        assert(l <= r);
        return FindLast(l, r, f, 1, 1, n);
    }
};
#undef ls
#undef rs

struct Info {
    int Min;
    Info (int x = inf) {
        Min = x;
    }
};

Info operator+ (const Info& x, const Info& y) {
    return Info { min(x.Min, y.Min) };
}

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    BlockCutTree BCT(n);
    for(int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        BCT.add(u, v);
    }
    BCT.work();

    auto [_, block, adj] = BCT.getTree();

    HLD hld(n + block);
    for(int i = 1; i <= n; ++i) {
        for(auto j : adj[i]) {
            hld.add(i, j);
        }
    }
    hld.work();

    vector<multiset<int>> S(block + 1);
    for(int i = 1; i <= block; ++i) {
        for(auto j : hld.adj[i + n]) {
            S[i].insert(a[j]);
        }
    }

    SegmentTree<Info> seg(n + block);
    for(int i = 1; i <= n + block; ++i) {
        seg.modify(hld.dfn[i], [&](Info& info) {
            info.Min = a[i];
        });
    }
    for(int i = 1; i <= block; ++i) {
        seg.modify(hld.dfn[i + n], [&](Info& info) {
            info.Min = *S[i].begin();
        });
    }

    while (q--) {
        char op;
        cin >> op;
        if (op == 'A') {
            int u, v;
            cin >> u >> v;
            int w = hld.lca(u, v);
            int ans = hld.query<Info>(u, v, [&](int l, int r) {
                return seg.query(l, r);
            }).Min;
            if (w > n) {
                int fa = hld.fa[w];
                if (fa) ans = min(ans, a[fa]);
            }
            cout << ans << endl;
        } else {
            int p, x;
            cin >> p >> x;
            int fa = hld.fa[p];
            if (fa) {
                fa -= n;
                auto it = S[fa].find(a[p]);
                S[fa].erase(it);
                S[fa].insert(x);
                seg.modify(hld.dfn[fa + n], [&](Info& info) {
                    info.Min = *S[fa].begin();
                });
            }
            a[p] = x;
            seg.modify(hld.dfn[p], [&](Info& info) {
                info.Min = x;
            });
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