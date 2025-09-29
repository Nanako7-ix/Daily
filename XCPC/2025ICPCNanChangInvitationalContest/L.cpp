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
 * Created: 2025/05/18 22:40:09
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

template<typename Info>
struct SegmentTree {
    int n, cnt;
    vector<Info> info;
    vector<int> ls, rs, ver;
    
    SegmentTree() = default;
    SegmentTree(int n, int m) {
        init(n, m);
    }

    template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
    SegmentTree(const Iterator& l, const Iterator& r, int m) {
        init(l, r, m);
    }

    void init(int n, int m) {
        vector<Info> _(n, Info{});
        init(_.begin(), _.end(), m);
    }

    template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
    void init(const Iterator& l, const Iterator& r, int m) {
        n = r - l;
        cnt = 0;
        int N = (n + m) << 5;
        ver.assign(m + 1, 0);
        ls.assign(N, 0);
        rs.assign(N, 0);
        info.assign(N, Info{});
        build(ver[0], 1, n, l);
    }

    void pull(int u) {
        info[u] = info[ls[u]] + info[rs[u]];
    }

    template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
    void build(int& u, int l, int r, const Iterator& it) {
        if(u == 0) u = ++cnt;
        if(l == r) {
            info[u] = *it;
            return;
        }
        int m = (l + r) >> 1;
        build(ls[u], l, m, it);
        build(rs[u], m + 1, r, it + (m - l + 1));
        pull(u);
    }

    template<typename Func>
    void modify(int p, Func&& op, int& u, int v, int l, int r) {
        u = ++cnt;
        ls[u] = ls[v], rs[u] = rs[v];
        if (l == r) {
            info[u] = info[v];
            op(info[u]);
            return;
        }
        int m = (l + r) >> 1;
        if (p <= m) modify(p, op, ls[u], ls[v], l, m);
        else modify(p, op, rs[u], rs[v], m + 1, r);
        pull(u);
    }

    template<typename Func>
    void modify(int v, int u, int p, Func&& op) {
        modify(p, op, ver[u], ver[v], 1, n);
    }

    Info query(int L, int R, int x, int y, int l, int r) {
        if (L <= l && r <= R) {
            return info[y] - info[x];
        }
        int m = (l + r) >> 1;
        if (R <= m) return query(L, R, ls[x], ls[y], l, m);
        if (L > m)  return query(L, R, rs[x], rs[y], m + 1, r);
        return query(L, R, ls[x], ls[y], l, m) + query(L, R, rs[x], rs[y], m + 1, r);
    }

    Info query(int x, int y, int l, int r) {
        assert(x <= y && l <= r);
        return query(l, r, ver[x], ver[y], 1, n);
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int cur = 0;
    vector<int> dep(n + 1), siz(n + 1), dfn(n + 1), idfn(n + 1);
    vector<vector<int>> fa(n + 1, vector<int> (__lg(n) + 1));
    auto dfs = [&](auto&& dfs, int u) -> void {
        dfn[u] = ++cur, siz[u] = 1;
        idfn[dfn[u]] = u;
        for (auto v : adj[u]) {
            if (v == fa[u][0]) continue;
            fa[v][0] = u;
            dep[v] = dep[u] + 1;
            dfs(dfs, v);
            siz[u] += siz[v];
        }
    };

    dfs(dfs, 1);
    for (int i = 1; i <= __lg(n); ++i) {
        for (int u = 1; u <= n; ++u) {
            fa[u][i] = fa[fa[u][i - 1]][i - 1];
        }
    }

    vector<int> _(n);
    iota(_.begin(), _.end(), 1);
    SparseTable lca(_.begin(), _.end(), [&](int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        while (dep[u] != dep[v]) {
            u = fa[u][__lg(dep[u] - dep[v])];
        }
        if (u == v) return u;
        for (int i = __lg(dep[u]); i >= 0; --i) {
            if (fa[u][i] != fa[v][i]) {
                u = fa[u][i], v = fa[v][i];
            }
        }
        return fa[u][0];
    });

    SegmentTree<int> seg(n, n);
    for (int i = 1; i <= n; ++i) {
        seg.modify(i - 1, i, idfn[i], [](int& x) { x = 1; });
    }

    while (q--) {
        int l, r, u;
        cin >> l >> r >> u;
        int cnt = seg.query(dfn[u] - 1, dfn[u] + siz[u] - 1, l, r);
        if (cnt == r - l + 1) {
            cout << lca(l, r) << endl;
        } else if (cnt == 0) {
            int x = lca(l, r);
            if (dfn[x] <= dfn[u] && dfn[u] <= dfn[x] + siz[x] - 1) {
                for (int i = __lg(dep[u]); i >= 0; --i) {
                    int v = max(fa[u][i], 1);
                    if (seg.query(dfn[v] - 1, dfn[v] + siz[v] - 1, l, r) == 0) {
                        u = v;
                    }
                }
                cout << fa[u][0] << endl;
            } else {
                cout << x << endl;
            }
        } else {
            cout << u << endl;
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