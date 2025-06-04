/**
 * Author: Nanako7_ix
 * Created: 2025/04/25 20:43:56
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
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1), p(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        p[a[i]] = i;
    }
    
    while (q--) {
        int l, r, x, ans;
        cin >> l >> r >> x;
        if (p[x] < l || p[x] > r) {
            ans = -1;
        } else {
            int lgood = 0, lbad = 0;
            int rgood = 0, rbad = 0;

            while (true) {
                int m = (l + r) >> 1;

                if (p[x] == m) break;

                if (p[x] > m) {
                    if (a[m] < x) rgood++;
                    if (a[m] > x) rbad++;
                    l = m + 1;
                }

                if (p[x] < m) {
                    if (a[m] < x) lbad++;
                    if (a[m] > x) lgood++;
                    r = m - 1;
                }
            }

            if (rgood + rbad >= x || lgood + lbad > n - x) {
                ans = -1;
            } else {
                ans = 2 * max(lbad, rbad);
            }
        }

        cout << ans << " \n"[!q];
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