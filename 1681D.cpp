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
 * Created: 2025/07/08 17:41:08
 * 好想和 めぐる 一起打 xcpc 啊
 */
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define debug(x) cerr << "\033[31m" << #x << " = " << x << "\033[0m\n"
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
    i64 n, x;
    cin >> n >> x;

    map<i64, int> dp {{ x,1 }};
    queue<i64> q;
    q.push(x);

    auto contains = [](i64 x, int i) -> bool {
        return to_string(x).contains(i + '0');
    };

    auto len = [](i64 x) -> int {
        int ans = 0;
        for (; x; ans++, x /= 10);
        return ans;
    };

    while (!q.empty()) {
        i64 u = q.front();
        q.pop();
        for (int i = 2; i <= 9; ++i) {
            if (!contains(u, i)) continue;
            i64 v = u * i;
            if (len(v) > n || dp[v]) continue;
            dp[v] = dp[u] + 1;
            q.push(v);
            if (len(v) == n) {
                cout << dp[v] - 1 << "\n";
                return;
            }
        }
    }

    cout << "-1\n";
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