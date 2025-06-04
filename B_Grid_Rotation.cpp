/**
 * Author:  Nanako7_ix
 * Created: 2025/05/04 02:38:18
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
    int n;
    cin >> n;
    vector<string> s(n), t(n);
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> t[i];
    }
    int ans = inf;
    for (int op = 0; op < 4; ++op) {
        int res = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                res += s[i][j] != t[i][j];
            }
        }
        ans = min(ans, res + op);
        auto ts = s;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                ts[j][n - 1 - i] = s[i][j];
            }
        }
        swap(s, ts);
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