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
 * Created: 2025/06/21 20:56:10
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

#define ls(u) ls[u]
#define rs(u) rs[u]
template<typename Info>
struct DynamicSegmentTree {
  using i64 = long long;
  int lo, hi, cnt;
  std::vector<Info> info;
  std::vector<int> ls, rs;

  DynamicSegmentTree () = default;

  DynamicSegmentTree (int N, int lo, int hi) { init(N, lo, hi); }

  void init (int N, int lo, int hi) {
    this -> lo = lo;
    this -> hi = hi;
    cnt = 0;
    info.assign(N, Info {});
    ls.assign(N, 0);
    rs.assign(N, 0);
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

    template<typename Func>
    int merge(int x, int y, int l, int r, Func&& op) {
        if(!x || !y) return x | y;
        if(l == r) {
            info[x] = op(info[x], info[y]);
        } else {
            int m = (l + r) >> 1;
            ls[x] = merge(ls[x], ls[y], l, m, op);
            rs[x] = merge(rs[x], rs[y], m + 1, r, op);
            pull(x);
        }
        return x;
    }

    template<typename Func>
    void merge(int& x, int y, Func&& op) {
        x = merge(x, y, lo, hi, op);
    }

    template<typename Func>
    int FindFirst(int L, int R, Func&& f, int u, int l, int r) {
        if(l > R || r < L || !f(info[u])) return inf;
        if(l == r) return l;
        int m = (l + r) >> 1;
        int res = FindFirst(L, R, f, ls(u), l, m);
        if(res == inf) res = FindFirst(L, R, f, rs(u), m + 1, r);
        return res;
    }
    
    template<typename Func>
    int FindLast(int L, int R, Func&& f, int u, int l, int r) {
        if(l > R || r < L || !f(info[u])) return -inf;
        if(l == r) return l;
        int m = (l + r) >> 1;
        int res = FindLast(L, R, f, rs(u), m + 1, r);
        if(res == -inf) res = FindLast(L, R, f, ls(u), l, m);
        return res;
    }
};
#undef ls
#undef rs

class DSU {
private:
    int n, cnt;
    std::vector<int> f, siz;
public:
    DSU() = default;

    DSU(int n) { init(n); }

    void init(int n) {
        this -> n = n;
        cnt = n;
        f.resize(n + 1);
        siz.assign(n + 1, 1);
        std::iota(f.begin(), f.end(), 0);
    }

    int find(int x) {
        if(f[x] == x) return x;
        return f[x] = find(f[x]);
    }

    bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return 0;
        cnt--, siz[x] += siz[y];
        return f[y] = x;
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    int size(int x) {
        return siz[find(x)];
    }

    int count() const {
        return cnt;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    DynamicSegmentTree<int> seg(m << 5, 1, n);
    vector<int> root(n + 1);
    vector<array<int, 2>> edges(m + 1);
    for (int i = 1; i <= m; ++i) {
        auto& [u, v] = edges[i];
        cin >> u >> v;
        seg.modify(root[u], v, [](int& x) { x = 1; });
        seg.modify(root[v], u, [](int& x) { x = 1; });
    }

    int q; cin >> q;
    DSU dsu(n);
    for (int i = 1; i <= n; ++i) {
        int _; cin >> _;
        auto [u, v] = edges[i];
        u = dsu.find(u);
        v = dsu.find(v);
        if (u == v) continue;
        if (seg.query(root[u], v, v) || seg.query(root[v], u, u)) {
            dsu.merge(u, v);
            seg.merge(root[u], root[v], bit_or {});
        }
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