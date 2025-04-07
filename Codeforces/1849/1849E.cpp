// Author: Nanako7_ix
// Created: 2025/04/07 16:02:42
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

template<typename T>
struct CartesianTree {
    int rt;
    vector<T> w;
    vector<int> ls, rs, fa;
    template<typename Iterator, typename Func, typename = _RequireInputIter<Iterator>>
    CartesianTree(const Iterator& l, const Iterator& r, Func&& f) : w(l, r) {
        int n = r - l;
        ls.assign(n + 1, 0);
        rs.assign(n + 1, 0);
        fa.assign(n + 1, 0);
        vector<int> stk;
        for(int i = 1; i <= n; ++i) {
            while(!stk.empty() && f(operator[](i), operator[](stk.back()))) {
                ls[i] = stk.back();
                stk.pop_back();
            }
            if(!stk.empty()) {
                fa[rs[stk.back()]] = i;
                rs[stk.back()] = i;
                fa[i] = stk.back();
            }
            stk.push_back(i);
        }
        while(stk.size() != 1) stk.pop_back();
        rt = stk.back();
    }
    const T& operator[](int i) const {
        return w[i - 1];
    }
};

template<typename Iterator, typename Func>
CartesianTree(const Iterator&, const Iterator&, Func&&) ->
CartesianTree<typename std::iterator_traits<Iterator>::value_type>;

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
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    CartesianTree tr(a.begin(), a.end(), greater<int> {});
    SparseTable Min(a.begin(), a.end(), [](int x, int y) {
        return min(x, y);
    });

    i64 ans = 0;
    [&](this auto &&dfs, int u, int l, int r) -> void {
        if(u == 0) return;
        dfs(tr.ls[u], l, u - 1);
        dfs(tr.rs[u], u + 1, r);
        if(u - l < r - u) {
            for(int i = l; i < u; ++i) {
                int lo = u, hi = r, res = -1;
                while(lo <= hi) {
                    int m = (lo + hi) >> 1;
                    if(Min(i, m) == Min(i, u)) {
                        res = m, lo = m + 1;
                    } else hi = m - 1;
                }

                assert(res != -1);
                ans += res - u + 1;
            }
        } else {
            for(int i = u; i <= r; ++i) {
                int lo = l, hi = u - 1, res = -1;
                while(lo <= hi) {
                    int m = (lo + hi) >> 1;
                    if(Min(m, u) == Min(m, i)) {
                        res = m, lo = m + 1;
                    } else hi = m - 1;
                }

                if(res == -1) break;
                ans += res - l + 1;
            }
        }

    } (tr.rt, 1, n);
    cout << ans << endl;
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