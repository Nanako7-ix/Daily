/**
 * Author:  Nanako7_ix
 * Created: 2025/05/04 03:40:52
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
    vector<int> a(n + 1), b(n + 1);
    // a[1] = inf;
    for (int i = 2; i <= n; ++i) {
        cin >> a[i];
    }
    for (int i = 2; i <= n; ++i) {
        cin >> b[i];
    }
    while (b[n] == 0) --n;

    int ans = 0;
    for (int i = n, nxt; i >= 2; ++ans, i = nxt) {
        nxt = i - 1;
        for (int j = i - 1; j >= i - a[i]; --j) {
            if (b[j]) {
                nxt = j;
                break;
            } else if (j - a[j] <= nxt - a[nxt]) {
                nxt = j;
            }
        }
        b[nxt] = 1;
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