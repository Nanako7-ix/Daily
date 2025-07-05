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
 * Created: 2025/06/18 17:21:23
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
using f64 = double;

constexpr int inf = 0x3f3f3f3f;
constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;

template<typename T>
struct Discrete {
    int ready;
    vector<T> a;

    Discrete() {
        init();
    }

    void init() {
        ready = 0, a.clear();
    }

    void insert(const T& v) {
        assert(!ready);
        a.push_back(v);
    }

    void work() {
        ready = 1;
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
    }

    int lower_bound(const T& v) {
        if(!ready) work();
        return ::lower_bound(a.begin(), a.end(), v) - a.begin() + 1;
    }

    int upper_bound(const T& v) {
        if(!ready) work();
        return ::upper_bound(a.begin(), a.end(), v) - a.begin() + 1;
    }

    T operator[](int k) {
        if(!ready) work();
        return a[k - 1];
    }

    int size() {
        if(!ready) work();
        return a.size();
    }
};

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
    int add;
    Tag (int add = 0) {
        this -> add = add;
    }
    void apply (const Tag& v) {
        add += v.add;
    }
};

struct Info {
    i64 Max;
    Info (i64 Max = 0) {
        this -> Max = Max;
    }
    void apply (const Tag& v) {
        Max += v.add;
    }
};

Info operator+ (const Info& x, const Info& y) {
    return Info { max(x.Max, y.Max) };
}

void solve() {
    int n;
    cin >> n;
    Discrete<i64> dis;
    vector<array<i64, 2>> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        auto& [l, r] = a[i];
        cin >> l >> r;
        dis.insert(l);
        dis.insert(r);
    }

    dis.work();    
    int N = dis.size();

    LazySegmentTree<Info, Tag> seg(N);
    for (int i = 1; i <= n; ++i) {
        auto [l, r] = a[i];
        l = dis.lower_bound(l);
        r = dis.lower_bound(r);
        i64 val = seg.query(r, r).Max;
        r = seg.FindFirst(1, N, [&](const Info& info) {
            return info.Max > val;
        });
        r = r == inf ? N : r - 1;
        seg.modify(l, r, 1);
        cout << seg.query(1, N).Max << " \n"[i == n];
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