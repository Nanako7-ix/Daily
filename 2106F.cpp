/**
 * Author: Nanako7_ix
 * Created: 2025/04/26 00:48:34
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
    int n;
    string s;
    cin >> n >> s;
    s = ' ' + s;

    vector<i64> f(n + 1), g(n + 1);
    for (int i = 1; i <= n; ++i) {
        if (s[i] == '1') continue;
        f[i] = i - 1;
        g[i] = n - i;
    }

    for (int i = 2; i <= n; ++i) {
        if (s[i] == '1') continue;
        if (s[i - 1] == '0') {
            f[i] += f[i - 1];
            g[i] += g[i - 1];
        }
    }
    
    for (int i = n - 1; i >= 1; --i) {
        if (s[i] == '1') continue;
        if (s[i + 1] == '0') {
            f[i] = f[i + 1];
            g[i] = g[i + 1];
        }
    }
    g[n] = f[1] = 0;

    i64 ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (s[i] == '0') {
            ans = max({ans, f[i], g[i]});
        } else {
            ans = max(ans, 1 + (i == 1 ? 0 : g[i - 1]) + (i == n ? 0 : f[i + 1]));
        }
    }

    cout << ans << endl;
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