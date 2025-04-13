/**
 * Author: Nanako7_ix
 * Created: 2025/04/11 19:20:02
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
    int n, k, cnt = 0;
    cin >> n >> k;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    
    for(int i = 0; i <= k; ++i) {
        k -= i - 1, cnt++;
    }
    cnt = min(cnt, n);

    vector<i64> lft(n + 1), rgt(n + 2);
    i64 now = 0;
    for(int i = 1; i <= n; ++i) {
        now += a[i];
        lft[i] = max(lft[i - 1], now);
    }
    now = 0;

    i64 ans = lft[cnt];
    for(int r = n; r >= n - cnt + 1; --r) {
        now += a[r];
        ans = max(ans, lft[cnt - (n - r + 1)] + now);
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