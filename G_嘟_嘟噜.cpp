// Author: Nanako7_ix
// Created: 2025/03/29 16:28:04
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

void solve() {
    int x, y, n;
    cin >> x >> y >> n;
    set<i64> a {0, y}, b {0, x};
    multiset<i64> c {y}, d {x};
    for(int i = 1; i <= n; ++i) {
        char op; int p;
        cin >> op >> p;
        if(op == 'H') {
            auto it = a.lower_bound(p);
            int l = *prev(it), r = *it;
            a.insert(p);
            c.erase(c.find(r - l));
            c.insert(r - p);
            c.insert(p - l);
            cout << *c.rbegin() * (*d.rbegin()) << endl;
        } else {
            auto it = b.lower_bound(p);
            int l = *prev(it), r = *it;
            b.insert(p);
            d.erase(d.find(r - l));
            d.insert(r - p);
            d.insert(p - l);
            cout << *d.rbegin() * (*c.rbegin()) << endl;
        }
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}