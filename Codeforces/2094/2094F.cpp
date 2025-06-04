/**
 * Author: Nanako7_ix
 * Created: 2025/04/14 00:23:29
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
    int n, m, k;
    cin >> n >> m >> k;
    
    if(m % k == 0) {
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                cout << (i + j) % k + 1 << " \n"[j == m - 1];
            }
        }
    } else {
        int now = 0;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                cout << now++ % k + 1 << " \n"[j == m - 1];
            }
        }
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