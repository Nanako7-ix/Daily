/**
 * Author:  Nanako7_ix
 * Created: 2025/05/03 00:46:26
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
    int n;
    cin >> n;

    bitset<200005> dp;
    dp[1] = 1;

    i64 ans = 0, sum = 0;
    for (int i = 1; i <= n; ++i) {
        int x; cin >> x;
        sum += x;
        dp |= dp << x;
        if (dp[i]) {
            ans = max(ans, sum - i + 1);
            dp[i] = 0;
        }
    }

    for (int i = n + 1; i <= 2 * n; ++i) {
        if (dp[i]) {
            ans = max(ans, sum - i + 1);
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