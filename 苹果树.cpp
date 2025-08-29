#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

/**
 * ds(dfn(*)) = a(*)
 * ds(*) = a(idfn(*))
 */

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
    T query(int u, int v, Func query, T res = {}) {
        while (top[u] != top[v]) {
            if (dep[top[u]] > dep[top[v]]) {
                res = query(dfn[top[u]], dfn[u]) + res;
                u = fa[top[u]];
            } else {
                res = query(dfn[top[v]], dfn[v]) + res;
                v = fa[top[v]];
            }
        }
        if (dep[u] < dep[v]) {
            return query(dfn[u], dfn[v]) + res;
        } else {
            return query(dfn[v], dfn[u]) + res;
        }
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

constexpr i64 inf = 1E12;

struct Info {
    array<array<i64, 3>, 3> mat;
    Info () {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                mat[i][j] = i == j ? 0 : -inf;
            }
        }
    }
    i64& a()   { return mat[1][2]; }
    i64& tag() { return mat[0][1]; }
};

Info operator+ (const Info& x, const Info& y) {
    Info res;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            res.mat[i][j] = max({
                x.mat[i][0] + y.mat[0][j],
                x.mat[i][1] + y.mat[1][j],
                x.mat[i][2] + y.mat[2][j],
            });
        }
    }
    return res;
}

void Thephix() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    HLD hld(n);
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        hld.add(u, v);
    }
    
    hld.work(1);
    SegmentTree<Info> seg(n);
    for (int i = 1; i <= n; ++i) {
        seg.modify(hld.dfn[i], [&](Info& info) {
            info.mat[1][1] = -inf;
            info.a()   = a[i];
            info.tag() = 0;
        });
    }

    auto query = [&](int x, int y) {
        int lca = hld.lca(x, y);
        Info res1 = hld.query(x, lca, [&](int l, int r) -> Info {
            return seg.query(l, r);
        });
        Info res2 = hld.query(y, lca, [&](int l, int r) -> Info {
            return seg.query(l, r);
        });

        i64 tag = lca == 1 ? 0 : seg.query(hld.dfn[hld.fa[lca]], hld.dfn[hld.fa[lca]]).tag();
        i64 ans1 = max(res1.mat[0][2], res1.mat[1][2] + tag);
        i64 ans2 = max(res2.mat[0][2], res2.mat[1][2] + tag);
        return max(ans1, ans2);
    };

    for (int i = 1; i <= m; ++i) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 1) {
            cout << query(x, y) << "\n";
        } else {
            seg.modify(hld.dfn[x], [&](Info& info) {
                info.tag() += y;
            });
            if (x != 1) {
                x = hld.fa[x];
                seg.modify(hld.dfn[x], [&](Info& info) {
                    info.a() += y;
                });
            }
        }
    }
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