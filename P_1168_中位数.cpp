// Author: Nanako7_ix
// Created: 2025/04/03 01:11:01
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
    int n;
    cin >> n;

    Tree<int> tr;
    for(int i = 1; i <= n; ++i) {
        int x; cin >> x;
        tr.insert(x);
        if(i & 1) {
            cout << tr.find_by_order(i / 2 + 1) << endl;
        }
    }
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}