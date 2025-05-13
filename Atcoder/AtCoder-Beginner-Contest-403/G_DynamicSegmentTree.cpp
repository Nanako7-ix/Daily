/**
 * Author:  Nanako7_ix
 * Created: 2025/04/29 18:19:27
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
constexpr int N = 1E9;

#define ls(u) ls[u]
#define rs(u) rs[u]
template<typename Info>
struct DynamicSegmentTree {
  using i64 = long long;
  int n, lo, hi, cnt;
  std::vector<Info> info;
  std::vector<int> ls, rs;

  DynamicSegmentTree () = default;

  DynamicSegmentTree (int n, int lo, int hi) { init(n, lo, hi); }

  void init (int n, int lo, int hi) {
    this -> n = n;
    this -> lo = lo;
    this -> hi = hi;
    cnt = 0;
    info.assign(n << 5, Info {});
    ls.assign(n << 5, 0);
    rs.assign(n << 5, 0);
  }

  void pull(int u) {
    info[u] = info[ls(u)] + info[rs(u)];
  }

  template<typename Func>
  void modify(int p, Func&& op, int& u, int l, int r) {
    if(u == 0) u = ++cnt;
    if(l == r) {
      op(info[u]);
      return;
    }
    int m = (l + r) >> 1;
    if(p <= m) modify(p, op, ls(u), l, m);
    else modify(p, op, rs(u), m + 1, r);
    pull(u);
  }

  template<typename Func>
  void modify(int& u, int p, Func&& op) {
    modify(p, op, u, lo, hi);
  }

  Info query(int L, int R, int u, int l, int r) {
    if(u == 0) return Info {};
    if(L <= l && r <= R) {
      return info[u];
    }
    int m = (l + r) >> 1;
    if(R <= m) return query(L, R, ls(u), l, m);
    if(L > m) return query(L, R, rs(u), m + 1, r);
    return query(L, R, ls(u), l, m) + query(L, R, rs(u), m + 1, r);
  }

  Info query(int u, int l, int r) {
    return query(l, r, u, lo, hi);
  }
};
#undef ls
#undef rs

struct Info {
    i64 odd, even;
    int len;
    Info () {
        odd = even = len = 0;
    }
};

Info operator+ (Info x, Info y) {
    if (x.len % 2 == 1) {
        x.odd += y.even;
        x.even += y.odd;
    } else {
        x.odd += y.odd;
        x.even += y.even;
    }
    x.len += y.len;
    return x;
}

void solve() {
    i64 n, last = 0;
    int rt = 0;
    cin >> n;

    DynamicSegmentTree<Info> seg(n, 1, N);

    for (int i = 1; i <= n; ++i) {
        i64 x; cin >> x;
        x = (x + last) % N + 1;
        seg.modify(rt, x, [&](Info& info) {
            if (info.len % 2 == 0) {
                info.odd += x;
            } else {
                info.even += x;
            }
            info.len++;
        });
        last = seg.query(rt, 1, N).odd;
        cout << last << endl;
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