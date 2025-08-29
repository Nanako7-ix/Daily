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
 * Created: 2025/05/22 18:17:14
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
    int n, k;
    cin >> n >> k;
    f64 p, L, R;
    vector<f64> r(n + 1), c(n + 1);
    cin >> r[0] >> c[0] >> p >> L >> R;

    vector<int> vis(n + 1);
    r[n] = L;
    vis[0] = vis[n] = 1;
    for (int i = 1; i <= k; ++i) {
        int x; cin >> x;
        vis[x] = 1;
        cin >> r[x];
    }

    vector<f64> pre(n + 1);
    pre[0] = 1;
    for (int i = 1; i <= n; ++i) {
        pre[i] = pre[i - 1] * p;
    }
    for (int i = 1; i <= n; ++i) {
        pre[i] += pre[i - 1];
    }

    for (int i = 0; i <= n; ++i) {
        if (vis[i]) continue;
        if ((1 - p) * pre[n - 1 - i] > 1) {
            r[i] = R;
        } else {
            r[i] = L;
        }
    }
    
    f64 ans = 0;
    for (int i = 1; i <= n; ++i) {
        c[i] = p * c[i - 1] + (1 - p) * r[i - 1];
        ans += c[i] - r[i];
    }
    cout << setpre(12) << ans << endl;
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