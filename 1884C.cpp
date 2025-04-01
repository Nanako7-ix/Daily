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

  LazySegmentTree(int n) { init(n); }

  template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
  LazySegmentTree(const Iterator& l, const Iterator& r) { init(l, r); }

  void init(int n) {
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
};
#undef ls
#undef rs

struct Tag {
    int add;
    Tag(int x = 0) {
        add = x;
    }
    void apply(const Tag& v) {
        add += v.add;
    }
};

struct Info {
    int Min, Max;
    Info (int x = 0) {
        Min = Max = x;
    }
    void apply(const Tag& v) {
        Min += v.add;
        Max += v.add;
    }
};

Info operator+ (Info x, Info y) {
    Info res;
    res.Min = min(x.Min, y.Min);
    res.Max = max(x.Max, y.Max);
    return res;
}

template<typename T>
struct Discrete {
  vector<T> a;
  Discrete() { init(); }
  void init() { a.clear(); }
  void insert(const T& v) { a.push_back(v); }
  void work() {
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
  }
  int lower_bound(const T& v) {
    return ::lower_bound(a.begin(), a.end(), v) - a.begin() + 1;
  }
  int upper_bound(const T& v) {
    return ::upper_bound(a.begin(), a.end(), v) - a.begin() + 1;
  }
  T operator[](int k) { return a[k - 1]; }
  int size() { return a.size(); }
};

void solve() {
    int n, m, MIN = inf, MAX = 0;
    cin >> n >> m;
    vector<array<int, 2>> a(n + 1);
    Discrete<int> dis;
    for(int i = 1; i <= n; ++i) {
        cin >> a[i][0] >> a[i][1];
        dis.insert(a[i][0]), dis.insert(a[i][1]);
        MIN = min(MIN, a[i][0]);
        MAX = max(MAX, a[i][1]);
    }
    dis.work();
    for(int i = 1; i <= n; ++i) {
        a[i][0] = dis.lower_bound(a[i][0]);
        a[i][1] = dis.lower_bound(a[i][1]);
    }
    
    m = dis.size() + (MIN != 1 || MAX != m);
    LazySegmentTree<Info, Tag> seg(dis.size() + (MIN != 1 || MAX != m));
    vector<vector<int>> pl(m + 1), pr(m + 1);
    for(int i = 1; i <= n; ++i) {
        pl[a[i][0]].push_back(a[i][1]);
        pr[a[i][1]].push_back(a[i][0]);
    }

    int ans = 0;
    for(int i = 1; i <= m; ++i) {
        for(auto r : pl[i]) {
            seg.modify(i, r, 1);
        }
        auto [Min, Max] = seg.query(1, m);
        ans = max(ans, Max - Min);
        for(auto l : pr[i]) {
            seg.modify(l, i, -1);
        }
    }
    cout << ans << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}