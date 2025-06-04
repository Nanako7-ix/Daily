/**
 * Author: Nanako7_ix
 * Created: 2025/04/24 23:42:41
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
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1), b(m + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for (int i = 1; i <= m; ++i) {
        cin >> b[i];
    }

    vector<int> f(n + 1), g(n + 2);
    for (int i = 1; i <= n; ++i) {
        f[i] = f[i - 1];
        if (f[i - 1] != m && a[i] >= b[f[i - 1] + 1]) {
            f[i] += 1;
        }
    }
    for (int i = n; i >= 1; --i) {
        g[i] = g[i + 1];
        if (g[i + 1] != m && a[i] >= b[m - g[i + 1]]) {
            g[i] += 1;
        }
    }

    if (f[n] == m) {
        cout << "0\n";
        return;
    }

    int ans = inf;
    for (int i = 1; i <= m; ++i) {
        int l = i == 1 ? 0 : lower_bound(f.begin() + 1, f.end(), i - 1) - f.begin();
        int r = i == m ? n + 1: upper_bound(g.begin() + 1, g.end(), m - i, greater {}) - g.begin() - 1;
        if (l < r) {
            ans = min(ans, b[i]);
        }
    }

    if (ans == inf) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
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