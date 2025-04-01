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
template<typename Info>
struct SegmentTree {
  int n;
  std::vector<Info> info;

  SegmentTree() = default;

  SegmentTree(int n) { init(n); }

  template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
  SegmentTree(const Iterator& l, const Iterator& r) { init(l, r); }

  void init(int n) {
    vector<Info> _(n);
    init(_.begin(), _.end());
  }

  template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
  void init(const Iterator& l, const Iterator& r) {
    n = r - l;
    info.assign(4 << std::__lg(n), Info{});
    build(1, 1, n, l);
  }

  void pull(int u) {
    info[u] = info[ls(u)] + info[rs(u)];
  }

  template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
  void build(int u, int l, int r, const Iterator& it) {
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
    int m = (l + r) >> 1;
    if (p <= m) modify(p, op, ls(u), l, m);
    else modify(p, op, rs(u), m + 1, r);
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
    if (R <= m) return query(L, R, ls(u), l, m);
    if (L > m)  return query(L, R, rs(u), m + 1, r);
    return query(L, R, ls(u), l, m) + query(L, R, rs(u), m + 1, r);
  }

  Info query(int l, int r) {
    assert(l <= r);
    return query(l, r, 1, 1, n);
  }
};
#undef ls
#undef rs

struct Info {
    int min, p;
    Info () = default;
    Info (int x, int y) {
        min = x, p = y;
    }
};

Info operator+(const Info& x, const Info& y) {
    if(x.min < y.min) {
        return x;
    } return y;
}

void solve() {
    i64 n, x;
    cin >> n >> x;
    vector<i64> a(n + 1), b(n + 1);
    SegmentTree<Info> seg(n);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i] >> b[i];
        seg.modify(i, [&](Info& info) {
            info.min = a[i], info.p = i;
        });
    }

    i64 ans = 0;
    for(int i = 1; i <= n; ++i) {
        int p = seg.query(1, n).p;
        if(p > 1 && a[p - 1] - a[p] > x) {
            i64 k = a[p - 1] - a[p] - x;
            ans += k, a[p - 1] -= k;
            seg.modify(p - 1, [&](Info& info) {
                info.min -= k;
            });
        }
        if(p < n && a[p + 1] - a[p] > x) {
            i64 k = a[p + 1] - a[p] - x;
            ans += k, a[p + 1] -= k;
            seg.modify(p + 1, [&](Info& info) {
                info.min -= k;
            });
        }
        seg.modify(p, [&](Info& info) {
            info.min = inf;
        });
    }
    
    i64 H = INF;
    for(int i = 1; i <= n; ++i) {
        H = min(H, a[i] + b[i]);
    }
    for(int i = 1; i <= n; ++i) {
        ans += a[i] + b[i] - H;
    }
    cout << ans << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}