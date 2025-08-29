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
 * Created: 2025/07/08 02:30:07
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
    int n, x;
    cin >> n >> x;
    vector<i64> pre(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> pre[i];
        pre[i] += pre[i - 1];
    }

    vector<i64> f(n + 1, -INF), g(n + 1);
    f[0] = 0;
    for (int l = 1; l <= n; ++l) {
        for (int r = l; r <= n; ++r) {
            int len = r - l + 1;
            f[len] = max(f[len], pre[r] - pre[l - 1]);
        }
    }

    for (int i = 0; i <= n; ++i) {
        i64 ans = -INF;
        for (int len = 0; len <= n; ++len) {
            ans = max(ans, f[len] + 1LL * min(i, len) * x);
        }
        cout << ans << " \n"[i == n];
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