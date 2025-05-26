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
 * Created: 2025/05/24 20:49:51
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
    int n, m;
    cin >> n >> m;
    vector<vector<i64>> a(n + 1, vector<i64> (m + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> a[i][j];
        }
    }

    i64 ans = 0;
    vector<vector<int>> vis(n + 1, vector<int> (m + 1));
    auto dfs = [&](auto dfs, int x, int y) {
        if (x == n + 1 && y == 1) {
            i64 res = 0;
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= m; ++j) {
                    if (vis[i][j] == 0) {
                        res ^= a[i][j];
                    }
                }
            }
            ans = max(ans, res);
            return;
        }
        if (x != n && vis[x][y] == 0 && vis[x + 1][y] == 0) {
            vis[x][y] = vis[x + 1][y] = 1;
            dfs(dfs, x + (y == m), y % m + 1);
            vis[x][y] = vis[x + 1][y] = 0;
        }
        if (y != m && vis[x][y] == 0 && vis[x][y + 1] == 0) {
            vis[x][y] = vis[x][y + 1] = 1;
            dfs(dfs, x + (y == m), y % m + 1);
            vis[x][y] = vis[x][y + 1] = 0;
        }
        dfs(dfs, x + (y == m), y % m + 1);
    };
    dfs(dfs, 1, 1);
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