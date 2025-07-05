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
 * Created: 2025/06/18 00:28:41
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
    cin >> n;
    vector a(3, vector<int> (n + 1));
    vector<array<int, 2>> pos(2 * n + 1);
    for (int i = 1; i <= 2; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> a[i][j];
            pos[a[i][j]] = array {i, j};
        }
    }

    vector<array<int, 2>> ans;

    auto op1 = [&](int p) {
        int x = a[1][p], y = a[1][p + 1];
        swap(pos[x], pos[y]);
        swap(a[1][p], a[1][p + 1]);
        ans.push_back({1, p});
    };

    auto op2 = [&](int p) {
        int x = a[2][p], y = a[2][p + 1];
        swap(pos[x], pos[y]);
        swap(a[2][p], a[2][p + 1]);
        ans.push_back({2, p});
    };

    auto op3 = [&](int p) {
        int x = a[1][p], y = a[2][p];
        swap(pos[x], pos[y]);
        swap(a[1][p], a[2][p]);
        ans.push_back({3, p});
    };

    for (int i = 1; i <= n; ++i) {
        auto& [x, y] = pos[i];
        if (x == 2) {
            while (y < i) op2(y);
            op3(y);
        }
        while (y > i) op1(y - 1);
    }
    for (int i = 1; i <= n; ++i) {
        auto& [x, y] = pos[i + n];
        assert(y >= i);
        while (y > i) op2(y - 1);
    }
    cout << ans.size() << "\n";
    for (auto [x, y] : ans) {
        cout << x << ' ' << y << "\n";
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