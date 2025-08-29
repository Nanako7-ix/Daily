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
 * Created: 2025/05/22 17:13:38
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

void solve() {
    int n, _;
    cin >> n >> _ >> _ >> _;
    vector<array<array<int, 2>, 3>> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i][0][0] >> a[i][1][0] >> a[i][2][0];
        cin >> a[i][0][1] >> a[i][1][1] >> a[i][2][1];
    }

    int ans = 0;
    for (int t = 0; t < 3; ++t) {
        vector<int> x;
        for (int i = 1; i <= n; ++i) {
            x.push_back(a[i][t][0]);
            x.push_back(a[i][t][1]);
        }
        sort(x.begin(), x.end());
        x.erase(unique(x.begin(), x.end()), x.end());
        int m = x.size();
        vector<int> f(m + 1);
        for (int i = 1; i <= n; ++i) {
            int l = lower_bound(x.begin(), x.end(), a[i][t][0]) - x.begin();
            int r = lower_bound(x.begin(), x.end(), a[i][t][1]) - x.begin();
            if (l > r) swap(l, r);
            f[l]++, f[r + 1]--;
        }
        int sum = 0;
        for (int i = 0; i < m; ++i) {
            sum += f[i];
            ans = max(ans, sum);
        }
    }

    cout << ans << endl;
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