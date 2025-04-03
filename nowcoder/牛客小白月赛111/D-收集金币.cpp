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
    int n, m;
    cin >> n >> m;
    vector<vector<i64>> a(n + 1, vector<i64> (m + 1));
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            cin >> a[i][j];
        }
    }
    int q; cin >> q;
    for(int i = 1; i <= q; ++i) {
        int x, y, t;
        cin >> x >> y >> t;
        if(x == 1 && y == 1) continue;
        if(t + 2 <= x + y) {
            a[x][y] = -INF;
        }
    }
    vector<vector<i64>> dp(n + 1, vector<i64> (m + 1, -INF));
    dp[1][1] = a[1][1];
    i64 ans = a[1][1];
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            if(i == 1 && j == 1) continue;
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + a[i][j];
            ans = max(ans, dp[i][j]);
        }
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