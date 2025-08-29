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
 * Author:  Thephix
 * Created: 2025/07/16 14:37:31
 * 好想和 めぐる 一起打 xcpc 啊
 */
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr int Tpx = 0;
constexpr int inf = 1E9;
constexpr i64 INF = 4E18;

constexpr int dir[4][2] {
    {0, 1}, {1, 0}, {0, -1}, {-1, 0}
};

void Meguru() {
    int n;
    cin >> n;
    vector<vector<int>> a(n + 1, vector<int> (n + 1));
    for (int x = (n + 1) / 2, y = x, i = 1, p = 3; ; ++i) {
        a[x][y] = i;
        if (i == n * n) break;
        int tx = x + dir[(p + 1) % 4][0];
        int ty = y + dir[(p + 1) % 4][1];
        if (a[tx][ty] == 0) {
            x = tx, y = ty, p = (p + 1) % 4;
        } else {
            x += dir[p][0], y += dir[p][1];
        }
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
        Meguru();
    }

    return Tpx;
}