/**
 *
 *  $$$$$$\  $$$$$$\  $$$$$$\  $$\       $$\       $$$$$$\  
 * $$  __$$\ \_$$  _|$$  __$$\ $$ |      $$ |     $$  __$$\ 
 * $$ /  \__|  $$ |  $$ /  $$ |$$ |      $$ |     $$ /  $$ |
 * $$ |        $$ |  $$$$$$$$ |$$ |      $$ |     $$ |  $$ |
 * $$ |        $$ |  $$  __$$ |$$ |      $$ |     $$ |  $$ |
 * $$ |  $$\   $$ |  $$ |  $$ |$$ |      $$ |     $$ |  $$ |
 *  $$$$$$ | $$$$$$\ $$ |  $$ |$$$$$$$$\ $$$$$$$$\ $$$$$$  |
 * \______/  \______|\__|  \__|\________|\________|\______/ 
 *
 * Author:  Nanako7_ix
 * Created: 2025/06/29 19:07:36
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
using f64 = double;

constexpr int inf = 0x3f3f3f3f;
constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;

void solve() {
    int n;
    string s;
    cin >> n >> s;
    vector<array<pair<int, string>, 3>> dp(n + 1);
    for (int i = 1; i <= n; ++i) {
        dp[i][0] = pair {(s[i - 1] != 'r') + min(dp[i - 1][1], dp[i - 1][2]).first, min(dp[i - 1][1], dp[i - 1][2]).second + 'r'};
        dp[i][1] = pair {(s[i - 1] != 'e') + min(dp[i - 1][0], dp[i - 1][2]).first, min(dp[i - 1][0], dp[i - 1][2]).second + 'e'};
        dp[i][2] = pair {(s[i - 1] != 'd') + min(dp[i - 1][0], dp[i - 1][1]).first, min(dp[i - 1][0], dp[i - 1][1]).second + 'd'};
    }
    cout << min_element(dp[n].begin(), dp[n].end()) -> second << "\n";
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