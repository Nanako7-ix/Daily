/**
 * Author:  Nanako7_ix
 * Created: 2025/05/10 22:06:08
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
constexpr int dir4[4][2] = {
    {1, 0}, {-1, 0}, {0, 1}, {0, -1}
};
constexpr string s = "^v<>";

void solve() {
    int n, m, ex, ey;
    cin >> n >> m;
    vector<string> a(n + 1);
    queue<array<int, 2>> q;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        a[i] = ' ' + a[i];
        for (int j = 1; j <= m; ++j) {
            if (a[i][j] == 'E') {
                q.push({i, j});
            }
        }
    }

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int tx = x + dir4[i][0];
            int ty = y + dir4[i][1];
            if (tx < 1 || tx > n || ty < 1 || ty > m || a[tx][ty] != '.') {
                continue;
            }
            a[tx][ty] = s[i];
            q.push({tx, ty});
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << a[i].substr(1) << endl;
    }
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