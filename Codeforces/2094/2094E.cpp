/**
 * Author: Nanako7_ix
 * Created: 2025/04/13 23:42:27
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
    vector<int> a(n + 1);

    array<int, 30> cnt {};
    i64 sum = 0;
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
        for(int k = 0; k < 30; ++k) {
            cnt[k] += a[i] >> k & 1;
        }
        sum += a[i];
    }
    i64 ans = 0;
    for(int i = 1; i <= n; ++i) {
        i64 res = sum;
        for(int k = 0; k < 30; ++k) {
            if(a[i] >> k & 1) {
                res += i64 (n - 2 * cnt[k]) << k;
            }
        }
        ans = max(ans, res);
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