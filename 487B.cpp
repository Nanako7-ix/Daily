/**
 * Author: Nanako7_ix
 * Created: 2025/04/16 17:41:38
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
    int n, s, m;
    cin >> n >> s >> m;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    SparseTable Max(a.begin() + 1, a.end(), [](int x, int y) {
        return max(x, y);
    });
    SparseTable Min(a.begin() + 1, a.end(), [](int x, int y) {
        return min(x, y);
    });

    vector<int> dp(n + 1, inf);
    dp[0] = 0;
    SegmentTree<Info> seg(dp.begin(), dp.end());

    for (int i = 1; i <= n; ++i) {
        int lo = 1, hi = i - m + 1, res = -1;

        auto check = [&](int x) -> bool {
            return Max(x, i) - Min(x, i) <= s;
        };

        while (lo <= hi) {
            int mid = (lo + hi) >> 1;
            if (check(mid)) {
                hi = mid - 1;
                res = mid;
            } else lo = mid + 1;
        }

        if (res != -1) {
            int ans = inf;
            dp[i] = seg.query(res - 1 + 1, i - m + 1).Min + 1;
            seg.modify(i + 1, [&](Info& info) {
                info.Min = dp[i];
            });
        }
    }

    cout << (dp[n] > n ? -1 : dp[n]) << endl;
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