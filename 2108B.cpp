/**
 * Author:  Nanako7_ix
 * Created: 2025/05/01 22:44:47
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
    int n, x;
    cin >> n >> x;

    if (x == 0) {
        if (n == 1) {
            cout << "-1\n";
        } else if (n % 2 == 1) {
            cout << n + 3 << endl;
        } else {
            cout << n << endl;
        }
        return;
    }
    if (x == 1) {
        if (n & 1) {
            cout << n << endl;
        } else {
            cout << n + 3 << endl;
        }
        return;
    }

    int p = __builtin_popcount(x);
    if (p >= n) {
        cout << x << endl;
    } else {
        n -= p;
        n += n & 1;
        cout << x + n << endl;
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