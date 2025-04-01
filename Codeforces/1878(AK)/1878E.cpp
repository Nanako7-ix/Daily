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

template<typename T, typename Func>
class SparseTable {
private:
    int n;
    Func op;
    std::vector<std::vector<T>> st;
public:
    SparseTable () = default;

    template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
    SparseTable (const Iterator& l, const Iterator& r, Func&& f) {
        op = f, init(l, r);
    }

    template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
    void init (const Iterator& l, const Iterator& r) {
        n = r - l;
        st.assign(std::__lg(n) + 1, std::vector<T> (n + 1));
        for (int i = 1; i <= n; ++i) {
            st[0][i] = *(l + i - 1);
        }
        for (int i = 1; i <= std::__lg(n); ++i) {
            for (int j = 1; j + (1 << i) - 1 <= n; ++j) {
                st[i][j] = op(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

  T operator () (int l, int r) {
      assert(l <= r);
      int k = std::__lg(r - l + 1);
      return op(st[k][l], st[k][r - (1 << k) + 1]);
  }

  T query (int l, int r) {
      T res {};  
      int len = r - l + 1;
      for (int i = 0, k = l; i <= std::__lg(len); ++i) {
          if(len >> i & 1) {
              res = k == l ? st[i][l] : op(res, st[i][k]);
              k += 1 << i;
          }
      }
      return res;
  }
};

template<typename Iterator, typename Func>
SparseTable (const Iterator&, const Iterator&, Func&&) ->
SparseTable<typename std::iterator_traits<Iterator>::value_type, Func>;

void solve() {
    int n; cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    SparseTable And(a.begin() + 1, a.end(), [](const int& x, const int& y) {
        return x & y;
    });
    int q; cin >> q;
    while(q--) {
        int x, k;
        cin >> x >> k;
        if(a[x] < k) {
            cout << -1 << " \n"[!q];
        } else {
            int l = x, r = n, res = -1;
            while(l <= r) {
                int m = (l + r) >> 1;
                if(And(x, m) >= k) {
                    res = m, l = m + 1;
                } else r = m - 1;
            }
            assert(~res);
            cout << res << " \n"[!q];
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