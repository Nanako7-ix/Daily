/**
 * Author:  Nanako7_ix
 * Created: 2025/05/09 19:47:50
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

void solve() {
    int n, m;
    cin >> n >> m;
    priority_queue<array<int, 2>, vector<array<int, 2>>, greater<array<int, 2>>> q;
    for (int i = 1; i <= n; ++i) {
        array<int, 2> x;
        cin >> x[0];
        x[1] = 0;
        q.push(x);
    }
    for (int i = 1; i <= m; ++i) {
        array<int, 2> x;
        cin >> x[0];
        x[1] = 1;
        q.push(x);
    }

    i64 ans = 0;
    array<i64, 2> sum {};
    while (!q.empty()) {
        auto [val, op] = q.top();
        q.pop();
        if (op == 0) {
            ans += 1LL * m * val - sum[1];
            sum[0] += val;
        } else {
            ans += 1LL * n * val - sum[0];
            sum[1] += val;
        }
    }
    cout << ans << endl;
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