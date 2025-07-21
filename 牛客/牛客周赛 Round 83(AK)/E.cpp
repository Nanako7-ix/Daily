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
    int n, k;
    cin >> n >> k;
    vector<i64> a(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    vector<vector<i64>> dp(n + 1, vector<i64> (k + 1, -INF));
    dp[0][0] = 0;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= k; ++j) {
            for(int nxt = i - 1; nxt >= max(0, i - 6); --nxt) {
                dp[i][j] = max(dp[i][j], dp[nxt][j - 1]);
            }
            dp[i][j] += a[i];
        }
    }
    i64 ans = -INF;
    for(int i = 1; i <= n; ++i) {
        ans = max(ans, dp[i][k]);
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