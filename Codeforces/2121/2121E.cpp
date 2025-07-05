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
 * Created: 2025/06/17 23:23:22
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
    string s, t;
    cin >> s >> t;
    int n = s.size();
    vector vis(n, vector (2, vector<int> (2, 0)));
    vector  dp(n, vector (2, vector<int> (2, inf)));
    [&](this auto&& dfs, int p, bool liml, bool limr) -> int {
        if (p == n) return 0;
        if (vis[p][liml][limr] == 0) {
            int l = liml ? s[p] - '0' : 0;
            int r = limr ? t[p] - '0' : 9;
            for (int i = l; i <= r; ++i) {
                dp[p][liml][limr] = min(
                    (i == s[p] - '0') + (i == t[p] - '0') + dfs(p + 1, liml && i == l, limr && i == r),
                    dp[p][liml][limr]
                );
            }
            vis[p][liml][limr] = 1;
        }
        return dp[p][liml][limr];
    } (0, 1, 1);

    cout << dp[0][1][1] << "\n";
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