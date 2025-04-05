// Author: Nanako7_ix
// Created: 2025/04/05 19:52:53
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

#define ls(u) (u << 1)
#define rs(u) (u << 1 | 1)
template<typename Info, typename Tag>
struct LazySegmentTree {
    using i64 = long long;
    static constexpr int inf = 0x3f3f3f3f;
    int n;
    std::vector<Info> info;
    std::vector<Tag>  tag;

    LazySegmentTree() = default;

    LazySegmentTree(int n, Info e = {}) { init(n, e); }

    template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
    LazySegmentTree(const Iterator& l, const Iterator& r) { init(l, r); }

    void init(int n, Info e = {}) {
        vector<Info> _(n, e);
        init(_.begin(), _.end());
    }

    template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
    void init(const Iterator& l, const Iterator& r) {
        n = r - l;
        info.assign(4 << std::__lg(n), Info {});
        tag.assign(4 << std::__lg(n), Tag {});
        build(1, 1, n, l);
    }

    void apply(int u, const Tag& v) {
        info[u].apply(v);
        tag[u].apply(v);
    }

    void pull(int u) {
        info[u] = info[ls(u)] + info[rs(u)];
    }

    void push(int u) {
        apply(ls(u), tag[u]);
        apply(rs(u), tag[u]);
        tag[u] = Tag{};
    }

    template<typename Iterator>
    void build(int u, int l, int r, Iterator it) {
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
        push(u);
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

    void modify(int L, int R, const Tag& v, int u, int l, int r) {
        if (L <= l && r <= R) {
            apply(u, v);
            return;
        }
        push(u);
        int m = (l + r) >> 1;
        if (L <= m) modify(L, R, v, ls(u), l, m);
        if (R > m) modify(L, R, v, rs(u), m + 1, r);
        pull(u);
    }

    void modify(int l, int r, const Tag& v) {
        assert(l <= r);
        modify(l, r, v, 1, 1, n);
    }

    Info query(int L, int R, int u, int l, int r) {
        if (L <= l && r <= R) {
            return info[u];
        }
        push(u);
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
        push(u);
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
        push(u);
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
        push(u);
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

struct Tag {
    int val;
    Tag (int x = -1) {
        val = x;
    }
    void apply (const Tag& v) {
        if(v.val != -1) {
            val = v.val;
        }
    }
};

struct Info {
    int val, len;
    Info () {
        len = 1;
    }
    void apply (const Tag& v) {
        if(v.val != -1) {
            val = len * v.val;
        }
    }
};

Info operator+ (const Info& x, const Info& y) {
    Info res;
    res.len = x.len + y.len;
    res.val = x.val + y.val;
    return res;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    vector<int> Pmin(n + 1, n + 1), Pmax(n + 1, n + 1);
    vector<int> stk;
    for(int i = n; i >= 1; --i) {
        while(!stk.empty() && a[i] <= a[stk.back()]) {
            stk.pop_back();
        }
        if(!stk.empty()) Pmin[i] = stk.back();
        stk.push_back(i);
    }
    stk.clear();
    for(int i = n; i >= 1; --i) {
        while(!stk.empty() && a[i] >= a[stk.back()]) {
            stk.pop_back();
        }
        if(!stk.empty()) Pmax[i] = stk.back();
        stk.push_back(i);
    }

    // vector<int> dp(n + 1);
    LazySegmentTree<Info, Tag> dp(n);
    int minp = 1, maxp = 1;
    for(int i = 2; i <= n; ++i) {
        if(a[i] > a[maxp]) {
            maxp = i;
        }
        if(a[i] < a[minp]) {
            minp = i;
        }
        // dp[i] = minp < maxp;
        dp.modify(i, [&](Info& info) {
            info.val = minp < maxp;
        });
    }

    i64 ans = 0;
    for(int i = 1; i <= n; ++i) {
        // dp[i] = 0;
        dp.modify(i, [](Info& info) {
            info.val = 0;
        });
        if(Pmin[i] > Pmax[i]) {
            // for(int j = Pmax[i]; j < Pmin[i]; ++j) {
            //     dp[j] = 1;
            // }
            dp.modify(Pmax[i], Pmin[i] - 1, 1);
        } else if(Pmin[i] < Pmax[i]) {
            // for(int j = Pmin[i]; j < Pmax[i]; ++j) {
            //     dp[j] = 0;
            // }
            dp.modify(Pmin[i], Pmax[i] - 1, 0);
        }
        // for(int j = i; j <= n; ++j) {
        //     ans += dp[j];
        // }
        ans += dp.query(i, n).val;
    }
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