/**
 * Author:  Nanako7_ix
 * Created: 2025/05/09 19:45:11
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
    vector<char> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    int Max = 0, p;
    for (int i = 1; i <= n; ++i) {
        int x, y;
        cin >> x;
        cin.ignore();
        cin >> y;
        if (x > Max) {
            Max = x, p = i;
        }
    }
    cout << a[p] << endl;
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