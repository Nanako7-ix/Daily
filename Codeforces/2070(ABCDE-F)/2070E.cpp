#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#define setpre(x) fixed << setprecision(x)
#define debug(x) cerr << #x << " = " << x << "\n"
#define endl "\n"
#define int i64
using namespace std;
using namespace __gnu_pbds;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

constexpr int inf = 0x3f3f3f3f;
constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;

constexpr int t[4] {0, 1, 2, 1};
constexpr int g(int len) {
    return (len - 1) / 4 + t[(len - 1) % 4];
}

template<typename T,
template<typename Node_CItr, typename Node_Itr, typename Cmp_Fn_, typename _Alloc_>
typename update = tree_order_statistics_node_update>
struct Tree : tree<pair<T, int>, null_type, less<pair<T, int>>, rb_tree_tag, update> {
using super = tree<pair<T, int>, null_type, less<pair<T, int>>, rb_tree_tag, update>;
  int idx = 0;
  void insert(const T& v) { super::insert({v, ++idx}); }
  void erase(const T& v) { super::erase(super::lower_bound({v, 0})); }
  T find_by_order(int k) { return super::find_by_order(k - 1) -> first; }
  int order_of_key(const T& v) { return super::order_of_key({v, 0}) + 1; }
  T prev(const T& v) { return find_by_order(order_of_key(v) - 1); }
  const T next(const T& v) { return find_by_order(order_of_key(v + 1)); }
};

void solve() {
    int n, ans = 0;
    string s;
    cin >> n >> s;
    vector<int> a(n + 1), f(n + 1);
    array<Tree<int>, 4> S {};
    S[0].insert(0);
    for(int i = 1; i <= n; ++i) {
        a[i] = a[i - 1] + (s[i - 1] == '1');
        f[i] = 4 * a[i] - i;
        for(int j = 0; j < 4; ++j) {
            int v = f[i] + 5 - 4 * t[(i - j + 3) % 4];
            ans += S[j].size() - S[j].order_of_key(v) + 1;
        } S[i % 4].insert(f[i]);
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