/**
 * Author: Nanako7_ix
 * Created: 2025/04/17 14:51:31
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

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    vector<i64> pre(n + 1);
    for(int i = 1; i <= n; ++i) {
        pre[i] = pre[i - 1] + a[i];
    }

    vector<int> rgt(n + 1, -1), stk;
    for(int i = n; i >= 0; --i) {
        while (!stk.empty() && pre[stk.back()] > pre[i]) {
            stk.pop_back();
        }
        if (!stk.empty()) {
            rgt[i] = stk.back();
            rgt[i] = max(rgt[i], rgt[rgt[i]]);
        }
        stk.push_back(i);
    }

    i64 ans = -INF, k = -1;
    for (int i = 0; i <= n; ++i) {
        i64 res = rgt[i] == -1 ? pre[n] : pre[n] - (pre[rgt[i]] - pre[i]);
        if (res > ans) {
            ans = res;
            k = pre[i];
        }
    }
    
    cout << k << endl;
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
    
    int T = 1;
    cin >> T;
    
    while (T--) {
        solve();
    }
    
    return 0;
}