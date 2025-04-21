/**
 * Author: Nanako7_ix
 * Created: 2025/04/19 20:35:42
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
    vector<array<int, 3>> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i][0] >> a[i][1] >> a[i][2];
    }

    auto p = [&](int i) -> double { return a[i][2] / 100.0; };
    auto s = [&](int i) -> double { return a[i][0]; };
    auto c = [&](int i) -> int { return a[i][1]; };

    vector<vector<double>> dp((1 << n), vector<double> (m + 1));
    for (int msk = 1; msk < (1 << n); ++msk) {
        for (int rest = 0; rest <= m; ++rest) {
            for (int i = 1; i <= n; ++i) {
                if ((msk >> (i - 1) & 1) == 0) {
                    continue;
                }
                if (rest - c(i) < 0) continue;
                dp[msk][rest] = max(
                    dp[msk][rest],
                    (1 - p(i)) * dp[msk][rest - c(i)] + p(i) * (dp[msk ^ (1 << (i - 1))][rest - c(i)] + s(i))
                );
            }
        }
    }
    cout << setpre(12) << dp[(1 << n) - 1][m] << endl;
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