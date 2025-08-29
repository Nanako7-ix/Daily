#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

constexpr i64 inf = 4E18;
constexpr int dir[4][2] = {
    {0, 1}, {1, 0}, {0, -1}, {-1, 0}
};

// void solve () {
//     int n, m;
//     cin >> n >> m;
//     vector<vector<int>> a(n + 1, vector<int> (m + 1));
//     for (int i = 1; i <= n; ++i) {
//         string s;
//         cin >> s;
//         for (int j = 1; j <= m; ++j) {
//             a[i][j] = s[j - 1] == '#';
//         }
//     }
// 
//     auto check = [&](int k) -> bool {
//         vector<vector<i64>> dp(n + 1, vector<i64> (m + 1, inf));
//         vector<vector<i64>> vis(n + 1, vector<i64> (m + 1));
//         deque<array<int, 2>> q;
//         q.push_back({1, 1});
//         dp[1][1] = 0;
//         while (!q.empty()) {
//             auto [x, y] = q.front();
//             q.pop_front();
//             if (vis[x][y]) continue;
//             vis[x][y] = 1;
//             for (int i = 0; i < 4; ++i) {
//                 int tx = x + dir[i][0];
//                 int ty = y + dir[i][1];
//                 if (tx < 1 || tx > n || ty < 1 || ty > m) {
//                     continue;
//                 }
//                 i64 res = dp[x][y];
//                 if (dp[x][y] == k) {
//                     if (a[tx][ty]) res = inf;
//                 } else if (dp[x][y] == 0) {
//                     if (a[tx][ty]) res = 1;
//                 } else {
//                     res++;
//                 }
//                 if (res < dp[tx][ty]) {
//                     dp[tx][ty] = res;
//                     if (dp[tx][ty] == dp[x][y]) {
//                         q.push_front({tx, ty});
//                     } else {
//                         q.push_back({tx, ty});
//                     }
//                 }
//             }
//         }
//         return dp[n][m] < inf;
//     };

//     int l = 0, r = n + m - 1, res = -1;
//     while (l <= r) {
//         int mid = (l + r) >> 1;
//         if (check(mid)) {
//             res = mid;
//             r = mid - 1;
//         } else l = mid + 1;
//     }

//     assert(res != -1);
//     cout << res << "\n";
// }

void solve () {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n + 1, vector<int> (m + 1));
    for (int i = 1; i <= n; ++i) {
        string s;
        cin >> s;
        for (int j = 1; j <= m; ++j) {
            a[i][j] = s[j - 1] == '#';
        }
    }
    
    vector<vector<int>> vis(n + 1, vector<int> (m + 1));
    auto bfs = [&](int sx, int sy, int v) -> void {
        queue<array<int, 2>> q;
        q.push({sx, sy});
        vis[sx][sy] = v;
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            for (int i = 0; i < 4; ++i) {
                int tx = x + dir[i][0];
                int ty = y + dir[i][1];
                if (tx < 1 || tx > n || ty < 1 || ty > m || vis[tx][ty] || a[tx][ty]) {
                    continue;
                }
                q.push({tx, ty});
                vis[tx][ty] = v;
            }
        }
    };

    bfs(1, 1, 1), bfs(n, m, 2);
    
    queue<array<int, 3>> q;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (vis[i][j] == 1) {
                q.push({i, j, 0});
            }
        }
    }
    while (!q.empty()) {
        auto [x, y, dis] = q.front();
        q.pop();
        for (int i = 0; i < 4; ++i) {
            int tx = x + dir[i][0];
            int ty = y + dir[i][1];
            if (tx < 1 || tx > n || ty < 1 || ty > m || vis[tx][ty] == 1) {
                continue;
            }
            if (vis[tx][ty] == 2) {
                cout << dis << "\n";
                return;
            }
            q.push({tx, ty, dis + 1});
            vis[tx][ty] = 1;
        }
    }
}

int main () {
    cin.tie(nullptr), cout.tie(nullptr) -> sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}