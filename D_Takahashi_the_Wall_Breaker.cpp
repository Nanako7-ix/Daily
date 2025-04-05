// Author: Nanako7_ix
// Created: 2025/04/05 20:31:04
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
constexpr int dir[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

void solve() {
    int n, m;
    cin >> n >> m;
    vector<string> s(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> s[i];
        s[i] = ' ' + s[i];
    }
    int sx, sy, ex, ey;
    cin >> sx >> sy >> ex >> ey;
    vector<vector<int>> dp(n + 1, vector<int> (m + 1, inf));
    vector<vector<int>> vis(n + 1, vector<int> (m + 1, 0));
    priority_queue<array<int, 3> , vector<array<int, 3>>, greater<array<int, 3>>> q;
    q.push({dp[sx][sy] = 0, sx, sy});
    while(!q.empty()) {
        auto [_, x, y] = q.top();
        q.pop();
        if(vis[x][y]) continue;
        vis[x][y] = 1;
        for(int i = 0; i < 4; ++i) {
            int tx = x + dir[i][0];
            int ty = y + dir[i][1];
            if(tx < 1 || tx > n || ty < 1 || ty > m) {
                continue;
            }
            if(s[tx][ty] == '.' && dp[tx][ty] > dp[x][y]) {
                dp[tx][ty] = dp[x][y];
                q.push({dp[tx][ty], tx, ty});
            }
            if(s[tx][ty] == '#') {
                if(dp[tx][ty] > dp[x][y] + 1) {
                    dp[tx][ty] = dp[x][y] + 1;
                    q.push({dp[tx][ty], tx, ty});
                }
                tx += dir[i][0];
                ty += dir[i][1];
                if(tx >= 1 && tx <= n && ty >= 1 && ty <= m && dp[tx][ty] > dp[x][y] + 1) {
                    dp[tx][ty] = dp[x][y] + 1;
                    q.push({dp[tx][ty], tx, ty});
                }
            }
        }
    }
    cout << dp[ex][ey] << endl;
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