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
 * Created: 2025/07/11 07:56:50
 * 好想和 めぐる 一起打 xcpc 啊
 */
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define debug(x) cerr << "\033[31m" << #x << " = " << x << "\033[0m\n"
using namespace std;
using namespace __gnu_pbds;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64 = double;

constexpr i64 inf = 1E18;

#define ls(u) (u << 1)
#define rs(u) (u << 1 | 1)
template<typename Info, typename Tag>
struct LazySegmentTree {
    using i64 = long long;
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

    i64 dfs(int L, int R, i64 x, int u, int l, int r) {
        if (L <= l && r <= R) {
            if (x % info[u].lcm == 0) {
                return info[u].sum;
            }
            if (info[u].gcd == info[u].lcm) {
                apply(u, std::gcd(x, info[u].gcd));
                return info[u].sum;
            }
        }
        push(u);
        int m = (l + r) >> 1;
        i64 ans;
        if (R <= m) {
            ans = dfs(L, R, x, ls(u), l, m);
        } else if (L > m) {
            ans = dfs(L, R, x, rs(u), m + 1, r);
        } else {
            ans = dfs(L, R, x, ls(u), l, m) + dfs(L, R, x, rs(u), m + 1, r);
        }
        pull(u);
        return ans;
    }

    i64 dfs(int l, int r, i64 x) {
        assert(l <= r);
        return dfs(l, r, x, 1, 1, n);
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
};
#undef ls
#undef rs

struct Tag {
    i64 val;
    Tag (i64 x = 0) {
        val = x;
    }
    void apply (const Tag& v) {
        if (v.val == 0) return;
        val = v.val;
    }
};

struct Info {
    i64 gcd, lcm, sum, len;
    Info (i64 x = 0) {
        gcd = lcm = sum = x;
        len = 1;
    }
    void apply (const Tag& v) {
        if (v.val == 0) return;
        gcd = lcm = v.val;
        sum = v.val * len;
    }
};

Info operator+ (const Info& x, const Info& y) {
    Info res {};
    res.gcd = std::gcd(x.gcd, y.gcd);
    if (x.lcm == inf || y.lcm == inf) {
        res.lcm = inf;
    } else {
        res.lcm = std::lcm(x.lcm, y.lcm);
        res.lcm = std::min<i64> (res.lcm, inf);
    }
    res.sum = x.sum + y.sum;
    res.len = x.len + y.len;
    return res;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<i64> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    
    LazySegmentTree<Info, Tag> seg(a.begin() + 1, a.end());
    while (m--) {
        int op, l, r, x;
        cin >> op >> l >> r >> x;
        if (op == 0) {
            seg.modify(l, r, x);
        } else {
            i64 ans = seg.dfs(l, r, x);
            cout << ans << "\n";
        }
    }
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