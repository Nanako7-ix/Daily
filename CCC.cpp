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
 * Created: 2025/06/21 20:07:41
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
    int n, m;
    cin >> n >> m;

    if (n == 1) {
        for (int i = 1; i <= m; ++i) {
            int p; cin >> p;
            cout << i % 2 << "\n";
        }
        return;
    }

    int ans = 0;
    vector<int> a(n + 1);
    for (int i = 1; i <= m; ++i) {
        int p; cin >> p;
        if (a[p] == 0) {
            if (p == 1) {
                if (a[2] == 0) ans++;
            } else if (p == n) {
                if (a[n - 1] == 0) ans++;
            } else if (a[p - 1] == 0 && a[p + 1] == 0) {
                ans++;
            } else if (a[p - 1] == 1 && a[p + 1] == 1) {
                ans--;
            }
        } else {
            if (p == 1) {
                if (a[2] == 0) ans--;
            } else if (p == n) {
                if (a[n - 1] == 0) ans--;
            } else if (a[p - 1] == 0 && a[p + 1] == 0) {
                ans--;
            } else if (a[p - 1] == 1 && a[p + 1] == 1) {
                ans++;
            }
        }
        a[p] ^= 1;
        cout << ans << "\n";
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