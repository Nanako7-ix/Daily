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

// template<typename T,
// template<typename Node_CItr, typename Node_Itr, typename Cmp_Fn_, typename _Alloc_>
// typename update = tree_order_statistics_node_update>
// struct Tree : tree<pair<T, int>, null_type, less<pair<T, int>>, rb_tree_tag, update> {
// using super = tree<pair<T, int>, null_type, less<pair<T, int>>, rb_tree_tag, update>;
//     int idx = 0;
//     void insert(const T& v) {
//         super::insert({v, ++idx});
//     }
//     void erase(const T& v) {
//         super::erase(super::lower_bound({v, 0}));
//     }
//     T find_by_order(int k) { 
//         return super::find_by_order(k - 1) -> first;
//     }
//     int order_of_key(const T& v) {
//         return super::order_of_key({v, 0}) + 1;
//     }
//     T prev(const T& v) {
//         return find_by_order(order_of_key(v) - 1);
//     }
//     const T next(const T& v) {
//         return find_by_order(order_of_key(v + 1));
//     }
// };

// template<typename Node_CItr, typename Node_Itr, typename Cmp_Fn_, typename _Alloc_>
// struct update {
// public:
//     using metadata_type = pair<i64, i64>;
//     void operator()(Node_Itr it, Node_CItr end_it) {
//         Node_Itr l = it.get_l_child();
//         Node_Itr r = it.get_r_child();
//         auto& [info, siz] = const_cast<pair<i64, i64> &>(it.get_metadata());
//         info = i64 {**it}, siz = 1;
//         if (l != end_it) {
//             info += l.get_metadata().info;
//             siz += l.get_metadata().siz;
//         }
//         if (r != end_it) {
//             info += r.get_metadata().info;
//             siz += r.get_metadata().siz;
//         }
//     }
//     virtual Node_CItr node_begin() const = 0;
//     virtual Node_CItr node_end() const = 0;
//     i64 order_of_key(i64 x) {
//         i64 ans = 0;
//         Node_CItr it = node_begin();
//         while (it != node_end()) {
//             Node_CItr l = it.get_l_child();
//             Node_CItr r = it.get_r_child();
//             if (Cmp_Fn()(x, **it))
//                 it = l;
//             else {
//                 ans++;
//                 if(l != node_end()) ans += l.get_metadata();
//                 it = r;
//             }
//         }
//     return ans;
//     }
// };

int cnt;
class AAA {
public:
    AAA() {
        cnt++;
    }
};

void solve() {
    vector<AAA> a(114514);
    cout << cnt << endl;
    // int n, m;
    // cin >> n >> m;
    // Tree<int> pbds;
    // for(int i = 1; i <= n; ++i) {
    //     int x; cin >> x;
    //     pbds.insert(x);
    // }

    // int lst = 0, ans = 0;
    // for(int i = 1; i <= m; ++i) {
    //     int op, x;
    //     cin >> op >> x;
    //     x ^= lst;
    //     if(op == 1) {
    //         pbds.insert(x);
    //     } else if(op == 2) {
    //         pbds.erase(x);
    //     } else if(op == 3) {
    //         lst = pbds.order_of_key(x);
    //         ans ^= lst;
    //     } else if(op == 4) {
    //         lst = pbds.find_by_order(x);
    //         ans ^= lst;
    //     } else if(op == 5) {
    //         lst = pbds.prev(x);
    //         ans ^= lst;
    //     } else {
    //         lst = pbds.next(x);
    //         ans ^= lst;
    //     }
    // }
    // cout << ans << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int Info = 1;
    // cin >> Info;
    while(Info--) solve();
    return 0;
}