/**
 * Author:  Nanako7_ix
 * Created: 2025/04/30 19:04:10
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
    int n, k;
    cin >> n >> k;
    vector<array<i64, 4>> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i][0] >> a[i][1] >> a[i][2] >> a[i][3];
    }

    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    shuffle(a.begin() + 1, a.end(), rng);

    int B = 4 * sqrt(k);

    vector<i64> dp(k + 1, INF);
    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        int E = i * k / n;
        for (int j = min(k, E + B); j >= max(1, E - B); --j) {
            dp[j] = min({
                dp[j],
                (j - 1 >= 0 ? dp[j - 1] : INF) + a[i][0],
                (j - 2 >= 0 ? dp[j - 2] : INF) + a[i][1],
                (j - 3 >= 0 ? dp[j - 3] : INF) + a[i][2],
                (j - 4 >= 0 ? dp[j - 4] : INF) + a[i][3]
            });
        }
    }
    cout << dp[k] << endl;
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