/**
 * Author:  Nanako7_ix
 * Created: 2025/05/05 22:36:29
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
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    int Max = *max_element(a.begin() + 1, a.end());
    if (*min_element(a.begin() + 1, a.end()) == Max) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        for (int i = 1; i <= n; ++i) {
            if (a[i] == Max) {
                cout << 1 << ' ';
            } else {
                cout << 2 << ' ';
            }
        }
        cout << endl;
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