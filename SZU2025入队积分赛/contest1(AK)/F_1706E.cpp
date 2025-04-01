#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
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

class DSU {
private:
    int n, cnt;
    std::vector<int> f, siz;
public:
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
        if (x == y) return 0;
        cnt--, siz[x] += siz[y], f[y] = x;
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
    int n, m, q;
    cin >> n >> m >> q;
    DSU dsu(n);
    vector<vector<array<int, 2>>> adj(n + 1);
    for(int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        if(dsu.merge(u, v)) {
            adj[u].push_back({v, i});
            adj[v].push_back({u, i});
        }
    }

    vector<int> dep(n + 1);
    vector fa(n + 1, vector (19, array<int, 2> {}));
    dep[1] = 1;
    [&](this auto &&dfs, int u) -> void {
        for(auto [v, w] : adj[u]) {
            if(v == fa[u][0][0]) continue;
            fa[v][0] = {u, w};
            dep[v] = dep[u] + 1;
            dfs(v);
        }
    } (1);
    for(int i = 1; i < 19; ++i) {
        for(int u = 1; u <= n; ++u) {
            auto [v, w] = fa[u][i - 1];
            fa[u][i] = { fa[v][i - 1][0], max(fa[v][i - 1][1], w) };
        }
    }

    vector<array<int, 2>> a(n + 1);
    for(int i = 1; i <= n; ++i) {
        a[i] = {i, 0};
    }

    SparseTable st(a.begin() + 1, a.end(), [&](const array<int, 2>& U, const array<int, 2>& V) {
        int u = U[0], v = V[0];
        int ans = max(U[1], V[1]);
        if (dep[u] > dep[v]) swap(u, v);
        while (dep[u] != dep[v]) {
            ans = max(ans, fa[v][__lg(dep[v] - dep[u])][1]);
            v = fa[v][__lg(dep[v] - dep[u])][0];
        }
        if (u == v) return array<int, 2> { u, ans };
        for (int i = 18; i >= 0; --i) {
            if (fa[u][i][0] != fa[v][i][0]) {
                ans = max({ans, fa[u][i][1], fa[v][i][1]});
                u = fa[u][i][0];
                v = fa[v][i][0];
            }
        }
        return array<int, 2> { fa[u][0][0], max({ans, fa[u][0][1], fa[v][0][1]}) };
    });

    for(int i = 1; i <= q; ++i) {
        int l, r;
        cin >> l >> r;
        cout << st(l, r)[1] << " \n"[i == q];
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}