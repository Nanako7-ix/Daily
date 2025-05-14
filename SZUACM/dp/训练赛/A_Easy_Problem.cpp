/**
 *
 * $$$$$$\  $$$$$$\  $$$$$$\  $$\       $$\       $$$$$$\  
 * $$  __$$\ \_$$  _|$$  __$$\ $$ |      $$ |     $$  __$$\ 
 * $$ /  \__|  $$ |  $$ /  $$ |$$ |      $$ |     $$ /  $$ |
 * $$ |        $$ |  $$$$$$$$ |$$ |      $$ |     $$ |  $$ |
 * $$ |        $$ |  $$  __$$ |$$ |      $$ |     $$ |  $$ |
 * $$ |  $$\   $$ |  $$ |  $$ |$$ |      $$ |     $$ |  $$ |
 * $$$$$$  | $$$$$$\ $$ |  $$ |$$$$$$$$\ $$$$$$$$\ $$$$$$  |
 * \______/  \______|\__|  \__|\________|\________|\______/ 
 *
 * Author:  Nanako7_ix
 * Created: 2025/05/13 12:47:34
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

map<int, char> mp {
    {1, 'h'},
    {2, 'a'},
    {3, 'r'},
    {4, 'd'},
};

void solve() {
    int n;
    string s;
    cin >> n >> s;
    s = ' ' + s;
    vector<i64> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    vector<array<i64, 5>> dp(n + 1);
    dp[0] = {0, INF, INF, INF, INF};
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= 4; ++j) {
            if (s[i] == mp[j + 1]) {
                dp[i][j] = dp[i - 1][j] + a[i];
            } else if (s[i] == mp[j]) {
                dp[i][j] = min(dp[i - 1][j - 1], dp[i - 1][j]);
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    cout << min({dp[n][0], dp[n][1], dp[n][2], dp[n][3]}) << endl;
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