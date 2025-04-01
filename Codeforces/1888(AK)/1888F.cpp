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

#define ls(u) (u << 1)
#define rs(u) (u << 1 | 1)
template<typename Info, typename Tag>
class LazySegmentTree {
private:
  int n;
  std::vector<Info> info;
  std::vector<Tag>  tag;
  static constexpr int inf = 0x3f3f3f3f;
public:
  LazySegmentTree() = default;

  LazySegmentTree(int n, Info e = {}) { init(n, e); }

  template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
  LazySegmentTree(const Iterator& l, const Iterator& r) { init(l, r); }

  void init(int n, Info e = {}) {
    this -> n = n;
    info.assign(4 << std::__lg(n), Info{});
    tag.assign(4 << std::__lg(n), Tag{});
  }

  template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
  void init(const Iterator& l, const Iterator& r) {
    n = r - l;
    info.assign(4 << std::__lg(n), Info{});
    tag.assign(4 << std::__lg(n), Tag{});
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
      info[u] = *it;
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
    if (p <= m) modify(p, op, ls(u), l, m);
    else modify(p, op, rs(u), m + 1, r);
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
    if (R <= m) return query(L, R, ls(u), l, m);
    if (L > m) return query(L, R, rs(u), m + 1, r);
    return query(L, R, ls(u), l, m) + query(L, R, rs(u), m + 1, r);
  }

  Info query(int l, int r) {
    assert(l <= r);
    return query(l, r, 1, 1, n);
  }

  template<typename Func>
  int lft(int L, int R, Func&& f, int u, int l, int r) {
    if(l > R || r < L || !f(info[u])) return inf;
    if(l == r) return l;
    int m = (l + r) >> 1;
    push(u);
    int res = lft(L, R, f, ls(u), l, m);
    if(res == inf) res = lft(L, R, f, rs(u), m + 1, r);
    return res;
  }

  template<typename Func>
  int lft(int l, int r, Func&& f) {
    assert(l <= r);
    return lft(l, r, f, 1, 1, n);
  }
};
#undef ls
#undef rs

struct Tag {
    i64 add;
    Tag (i64 v = 0) { add = v; }
    void apply (const Tag& v) {
        add += v.add;
    }
};

struct Info {
    i64 min, max;
    Info (i64 x = 0) { min = max = x; }
    void apply (const Tag& v) {
        min += v.add, max += v.add;
    }
};

Info operator+ (const Info& x, const Info& y) {
    Info res;
    res.max = max(x.max, y.max);
    res.min = min(x.min, y.min);
    return res;
}

void solve() {
    int n; cin >> n;
    vector<i64> a(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    int q; cin >> q;
    vector<vector<array<i64, 2>>> pos(n + 2);
    for(int i = 2; i <= q + 1; ++i) {
        i64 l, r, x;
        cin >> l >> r >> x;
        pos[l].push_back({i, x});
        pos[r + 1].push_back({i, -x});
    }

    LazySegmentTree<Info, Tag> seg(q + 1, Info{0});
    for(int i = 1; i <= n; ++i) {
        for(auto [p, v] : pos[i]) {
            seg.modify(p, q + 1, v);
        }
        i64 x = seg.query(1, q + 1).min;
        cout << a[i] + x << " \n"[i == n];
        while (1) {
            int p = seg.lft(1, q + 1, [&](const Info& v) {
                return v.max > x;
            });
            if(p == inf) break;
            seg.modify(p, [&](Info& v) {
                v.max = -INF, v.min = INF;
            });
        }
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}