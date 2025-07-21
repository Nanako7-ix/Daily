// Author: Nanako7_ix
// Created: 2025/04/06 20:01:59
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

void solve() {
    int n, q;
    cin >> n >> q;
    vector<i64> a(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    vector<int> fa(n + 1);
    vector<vector<int>> adj(n + 1);
    for(int i = 2; i <= n; ++i) {
        int p; cin >> p;
        adj[p].push_back(i);
        fa[i] = p;
        a[i] += a[p];
    }

    int idx = 0;
    vector<int> dfn(n + 1), siz(n + 1);
    auto dfs = [&](auto &&dfs, int u) -> void {
        dfn[u] = ++idx;
        siz[u] = 1;
        for(auto v : adj[u]) {
            dfs(dfs, v);
            siz[u] += siz[v];
        }
    };
    dfs(dfs, 1);

    vector<i64> b(n + 1);
    for(int i = 1; i <= n; ++i) {
        b[dfn[i]] = a[i];
    }
    SparseTable Max(b.begin() + 1, b.end(), [](i64 x, i64 y) {
        return max(x, y);
    });
    for(int i = 1; i <= q; ++i) {
        int x, y;
        cin >> x >> y;
        int l = dfn[x], r = dfn[x] + siz[x] - 1;
        i64 ans = Max(l, r) - a[fa[x]] + a[y];
        if(l > 1) ans = max(ans, Max(1, l - 1));
        if(r < n) ans = max(ans, Max(r + 1, n));
        cout << ans << endl;
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