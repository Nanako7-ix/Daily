/**
 * Author:  Nanako7_ix
 * Created: 2025/05/11 23:11:14
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

int dir[4][2] = {
    {0, 1}, {1, 0}, {0, -1}, {-1, 0}
};

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> a(n + 1, vector<int> (n + 1));
    int x = (n + 1) / 2, y = (n + 1) / 2;
    for (int i = 1, t = 0, d = 1; i <= n * n; ++i) {
        a[x][y] = i;
        if ((2 * d - 1) * (2 * d - 1) == i) ++d;
        int tx = x + dir[t][0];
        int ty = y + dir[t][1];
        if (max(abs(tx - (n + 1) / 2), abs(ty - (n + 1) / 2)) >= d) {
            t = (t + 1) % 4;
            tx = x + dir[t][0];
            ty = y + dir[t][1];
        }
        x = tx, y = ty;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cout << a[i][j] - 1 << " \n"[j == n];
        }
    }
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