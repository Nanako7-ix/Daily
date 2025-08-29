#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

constexpr int Thephix = 0;
constexpr int N = 2000005;

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
    Tag (int x = 0) {
        val = x;
    }
    void apply (const Tag& v) {
        val += v.val;
    }
};

struct Info {
    int Max, p;
    Info (int x = 0) {
        Max = 0, p = x;
    }
    void apply (const Tag& v) {
        Max += v.val;
    }
};

Info operator+ (const Info& x, const Info& y) {
    if (x.Max >= y.Max) {
        return x;
    } else {
        return y;
    }
}

template<typename Info>
struct ChthollyTree {
    struct Node {
        i64 l, r;
        mutable Info v;
        Node (i64 l, i64 r, Info v) {
            this -> l = l;
            this -> r = r;
            this -> v = v;
        }
        bool operator< (const Node& o) const {
            return l < o.l;
        }
    };

    int n;
    set<Node> odt;
    ChthollyTree () = default;

    ChthollyTree (int n, Info v = {}) {
        init(n, v);
    }

    void init (int n, Info v = {}) {
        this -> n = n;
        odt.clear();
        odt.emplace(1, n, v);
    }

    set<Node>::iterator split(int p) {
        if (p == n + 1) return odt.end();
        auto it = odt.lower_bound(Node {p, 0, 0});
        if (it != odt.end() && it->l == p) return it;
        --it;
        auto [l, r, v] = *it;
        odt.erase(it);
        odt.emplace(l, p - 1, v);
        return odt.emplace(p, r, v + p - l).first;
    }

    void assign (int l, int r, Info v) {
        auto itr = split(r + 1);
        auto itl = split(l);
        odt.erase(itl, itr);
        odt.emplace(l, r, v);
    }

    template<typename Func>
    void perform(int l, int r, Func&& opt) {
        auto itr = split(r + 1);
        auto itl = split(l);
        for (auto it = itl; it != itr; ++it) {
            auto [l, r, v] = *it;
            opt(l, r, v);
        }
    }
};

void solve () {
    int n, m;
    cin >> n >> m;

    vector<int> id(2 * n);
    iota(id.begin(), id.end(), 1);
    LazySegmentTree<Info, Tag> seg(id.begin(), id.end());
    ChthollyTree<int> odt(n);
    
    for (int i = 1; i <= n; ++i) {
        int x; cin >> x;
        seg.modify(x, [](Info& info) {
            info.Max++;
        });
        odt.assign(i, i, x);
    }

    auto query = [&]() {
        auto [Max, p] = seg.query(1, 2 * n);
        cout << p << ' ' << Max << "\n";
    };

    query();

    for (int i = 1; i <= m; ++i) {
        int l, r, d;
        cin >> l >> r >> d;
        odt.perform(l, r, [&](int x, int y, int v) {
            seg.modify(v, v + y - x, -1);
        });
        seg.modify(d, d + r - l, 1);
        odt.assign(l, r, d);
        query();
    }
}

int main () {
    cin.tie(nullptr), cout.tie(nullptr);
    ios::sync_with_stdio(false);

    int T = 1;
    cin >> T;
    while (T--) {
        solve ();
    }

    return Thephix;
}