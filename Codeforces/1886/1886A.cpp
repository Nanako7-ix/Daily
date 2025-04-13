/**
 * Author: Nanako7_ix
 * Created: 2025/04/12 16:33:37
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
    array<int, 3> ans {};
    if(n % 3 == 0) {
        ans[0] = 1, ans[1] = 4, ans[2] = n - 5;
    } else {
        ans[0] = 1, ans[1] = 2, ans[2] = n - 3;
    }
    ranges::sort(ans);
    if(ans[0] > 0 && ans[1] > 0 && ans[2] > 0 && ans[0] != ans[1] && ans[1] != ans[2]) {
        cout << "YES\n" << ans[0] << ' ' << ans[1] << ' ' << ans[2] << endl;
    } else cout << "NO\n";
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