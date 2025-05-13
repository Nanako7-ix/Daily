/**
 * Author: Nanako7_ix
 * Created: 2025/04/27 20:17:11
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
constexpr int N = 1000000;
void solve() {
    int n, d;
    cin >> n >> d;
    vector<int> cnt(N + 1);
    for (int i = 1; i <= n; ++i) {
        int x; cin >> x;
        cnt[x]++;
    }

    if (d == 0) {
        int ans = 0;
        for (int i = 0; i <= N; ++i) {
            ans += max(0, cnt[i] - 1);
        }
        cout << ans << endl;
        return;
    }

    vector<array<int, 2>> dp(N + 1);
    for (int i = 0; i <= N; ++i) {
        dp[i][0] = cnt[i] + (i < d ? 0 : min(dp[i - d][0], dp[i - d][1]));
        dp[i][1] = i < d ? 0 : dp[i - d][0];
    }
    
    int ans = 0;
    for (int i = 0; i < d; ++i) {
        ans += min(dp[N - i][0], dp[N - i][1]);
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