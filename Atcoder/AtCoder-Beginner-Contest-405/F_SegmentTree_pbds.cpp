/**
 * Author:  Nanako7_ix
 * Created: 2025/05/10 22:55:06
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

template <typename T>
struct Tree {
    __gnu_pbds::tree<int, __gnu_pbds::null_type, less_equal<>,
        __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> t;
    auto size() const { return t.size(); }
    auto empty() const { return t.empty(); }
    auto begin() const { return t.begin(); }
    auto end() const { return t.end(); }
    auto clear() { return t.clear(); }
    auto min() const { return *t.begin(); }
    auto max() const { return *t.rbegin(); }
    auto insert(const T &x) { return t.insert(x); }
    auto erase(const T &x) { return t.erase(t.upper_bound(x)); }
    auto order_of_key(const T &x) const { return t.order_of_key(x); }
    auto find_by_order(const T &x) const { return *t.find_by_order(x); }
    auto lower_bound(const T &x) const { return *t.upper_bound(x); }
    auto upper_bound(const T &x) const { return *t.lower_bound(x); }
    auto prev(const T &x) const { return *--t.upper_bound(x); }
    auto next(const T &x) const { return *t.lower_bound(x); }
};

#define ls(u) (u << 1)
#define rs(u) (u << 1 | 1)
struct SegmentTree {
    int n;
    std::vector<array<Tree<int>*, 2>> info;

    SegmentTree(int n) {
        this -> n = 2 << __lg(n);
        info.assign(4 << std::__lg(n), array<Tree<int>*, 2> {});
    }

    void modify(int L, int R, int u, int l, int r) {
        if (L <= l && r <= R) {
            if (info[u][0] == nullptr) {
                info[u][0] = new Tree<int>;
            }
            if (info[u][1] == nullptr) {
                info[u][1] = new Tree<int>;
            }
            info[u][0] -> insert(R);
            info[u][1] -> insert(L);
            return;
        }
        int m = (l + r) >> 1;
        if (L <= m) modify(L, R, ls(u), l, m);
        if (R > m) modify(L, R, rs(u), m + 1, r);
    }

    void modify(int l, int r) {
        modify(l, r, 1, 1, n);
    }

    i64 query(int p, int u, int l, int r, int op, int L, int R) {
        i64 ans = 0;
        if (info[u][op]) {
            const Tree<int>& tr = *info[u][op];
            ans += tr.order_of_key(R) - tr.order_of_key(L);
        }
        if (l != r) {
            int m = (l + r) >> 1;
            if (p <= m) ans += query(p, ls(u), l, m, op, L, R);
            else ans  += query(p, rs(u), m + 1, r, op, L, R);
        }
        return ans;
    }

    i64 query(int p, int op, int l, int r) {
        return query(p, 1, 1, n, op, l, r);
    }
};
#undef ls
#undef rs

void solve() {
    int n, m;
    cin >> n >> m;
    SegmentTree seg(2 * n);
    for (int i = 1; i <= m; ++i) {
        int l, r;
        cin >> l >> r;
        seg.modify(l, r);
    }

    int q; cin >> q;
    for (int i = 1; i <= q; ++i) {
        int l, r;
        cin >> l >> r;
        cout << seg.query(l, 0, l, r) + seg.query(r, 1, l, r) << endl;
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