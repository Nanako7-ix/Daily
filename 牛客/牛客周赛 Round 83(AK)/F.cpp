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
    int n, m, h;
    cin >> n >> m >> h;
    vector<string> a(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
        a[i] = ' ' + a[i];
    }

    int sx, sy, ex, ey;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            if(a[i][j] == '*') {
                sx = i, sy = j;
            }
            if(a[i][j] == '%') {
                ex = i, ey = j;
            }
        }
    }

    vector dp(n + 1, vector<array<i64, 3>> (m + 1, array<i64, 3> {INF, INF, INF}));
    vector vis(n + 1, vector<array<i64, 3>> (m + 1, array<i64, 3> {}));
    priority_queue<array<i64, 4>, vector<array<i64, 4>>, greater<array<i64, 4>>> q;
    q.push({0, sx, sy, 0});
    dp[sx][sy][0] = 0;
    while(!q.empty()) {
        auto [w, x, y, op] = q.top();
        q.pop();
        if(vis[x][y][op]) continue;
        vis[x][y][op] = 1;
        if(x == n) continue;
        if(a[x + 1][y] != '#') {
            if(dp[x + 1][y][0] > w + 1) {
                dp[x + 1][y][0] = w + 1;
                q.push({dp[x + 1][y][0], x + 1, y, 0});
            }
        } else {
            if(op == 0 && dp[x + 1][y][0] > w + h + 1) {
                dp[x + 1][y][0] = w + h + 1;
                q.push({dp[x + 1][y][0], x + 1, y ,0});
            }
            if(y > 1 && a[x][y - 1] != '#' && dp[x][y - 1][2] > w + 1) {
                dp[x][y - 1][2] = w + 1;
                q.push({dp[x][y - 1][2], x, y - 1, 2});
            }
            if(y < m && a[x][y + 1] != '#' && dp[x][y + 1][1] > w + 1) {
                dp[x][y + 1][1] = w + 1;
                q.push({dp[x][y + 1][1], x, y + 1, 1});
            }
        }
    }
    i64 ans = min({dp[ex][ey][0], dp[ex][ey][1], dp[ex][ey][2]});
    cout << (ans == INF ? -1 : ans) << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}