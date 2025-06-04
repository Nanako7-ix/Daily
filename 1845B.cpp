/**
 * Author: Nanako7_ix
 * Created: 2025/04/17 14:16:57
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
    array<int, 2> a, b, c;
    cin >> a[0] >> a[1];
    cin >> b[0] >> b[1];
    cin >> c[0] >> c[1];
    b[0] -= a[0], c[0] -= a[0];
    b[1] -= a[1], c[1] -= a[1];
    int ans = 0;
    if ((b[0] <= 0 && c[0] <= 0) || (b[0] >= 0 && c[0] >= 0)) {
        ans += min(abs(b[0]), abs(c[0]));
    }
    if ((b[1] <= 0 && c[1] <= 0) || (b[1] >= 0 && c[1] >= 0)) {
        ans += min(abs(b[1]), abs(c[1]));
    }
    cout << ans + 1 << endl;
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