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

vector dp(60, vector (60, vector<i64> (60, 4e18)));
vector ddp(60, vector<i64> (60, 4e18));
void solve() {
    i64 x, y;
    cin >> x >> y;
    i64 ans = 4e18;
    for(int i = 0; i < 60; ++i) {
        for(int j = 0; j < 60; ++j) {
            if((x >> i) == (y >> j)) ans = min(ans, ddp[i][j]);
        }
    }
    cout << ans << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    dp[0][0].assign(60, 0);
    ddp[0][0] = 0;
    for(int i = 0; i < 60; ++i) {
        for(int j = 0; j < 60; ++j) {
            if(i == 0 && j == 0) continue;
            for(int k = 1; k < 60; ++k) {
                dp[i][j][k] = dp[i][j][k - 1];
                if(i >= k) dp[i][j][k] = min(dp[i][j][k], dp[i - k][j][k - 1] + (1LL << k));
                if(j >= k) dp[i][j][k] = min(dp[i][j][k], dp[i][j - k][k - 1] + (1LL << k));
                ddp[i][j] = min(ddp[i][j], dp[i][j][k]);
            }
        }
    }
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}