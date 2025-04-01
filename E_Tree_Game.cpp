#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#define setpre(x) fixed << setprecision(x)
#define debug(x) cerr << #x << " = " << x << "\n"
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

void solve() {
    int n;
    cin >> n;
    LCA lca(n);
    vector<vector<int>> a(n + 1, vector<int> (n + 1));
    for(int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        a[u][v] = a[v][u] = 1;
        lca.add(u, v);
    }
    lca.work();
    set<array<int, 2>> S;
    for(int i = 1; i <= n; ++i) {
        for(int j = i + 1; j <= n; ++j) {
            if(a[i][j]) continue;
            if((lca.dep[i] - lca.dep[j]) & 1) {
                S.insert({i, j});
            }
        }
    }

    if(S.size() & 1) {
        cout << "First" << endl;
    } else cout << "Second" << endl; 

    auto Me = [&]() -> void {
        auto it = S.begin();
        auto [u, v] = *it;
        cout << u << ' ' << v << endl;
        S.erase(it);
    };

    auto You = [&]() -> void {
        int u, v;
        cin >> u >> v;
        if(u > v) swap(u, v);
        S.erase({u, v});
    };

    while(S.size()) {
        if(S.size() & 1) {
            Me(), You();
        } else {
            You(), Me();
        }
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}