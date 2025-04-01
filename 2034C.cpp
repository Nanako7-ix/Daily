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
    vector<string> a(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
        a[i] = ' ' + a[i];
    }

    vector<vector<int>> dp(n + 1, vector<int> (m + 1));
    auto dfs = [&](this auto &&dfs, int x, int y) -> void {
        auto check = [&](int tx, int ty) {
            if(tx < 1 || tx > n || ty < 1 || ty > m) {
                return 1;
            }
            if(dp[tx][ty] == 0) {
                dp[x][y] = 2;
                dfs(tx, ty);
            }
            return dp[tx][ty] == 2 ? -1 : dp[tx][ty];
        };
        if(a[x][y] == 'U') {
            dp[x][y] = check(x - 1, y);
        } else if(a[x][y] == 'D') {
            dp[x][y] = check(x + 1, y);
        } else if(a[x][y] == 'L') {
            dp[x][y] = check(x, y - 1);
        } else if(a[x][y] == 'R') {
            dp[x][y] = check(x, y + 1);
        } else {
            dp[x][y] = min({check(x + 1, y), check(x - 1, y), check(x, y - 1), check(x, y + 1)});
        }
    };

    int ans = 0;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            if(dp[i][j] == 0) {
                dfs(i, j);
            }
            ans += dp[i][j] == -1;
        }
    }
    cout << ans << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}