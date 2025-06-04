/**
 * Author: Nanako7_ix
 * Created: 2025/04/24 23:32:04
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
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1), b(n + 1);

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    
    int sum = -1;
    for (int i = 1; i <= n; ++i) {
        cin >> b[i];
        if (b[i] != -1) {
            sum = a[i] + b[i];
        }
    }
    
    if (sum == -1) {
        cout << k + *min_element(a.begin() + 1, a.end()) - *max_element(a.begin() + 1, a.end()) + 1 << endl; 
    } else {
        for (int i = 1; i <= n; ++i) {
            if (b[i] == -1) {
                b[i] = sum - a[i];
            }
            if (b[i] < 0 || b[i] > k || a[i] + b[i] != sum) {
                cout << 0 << endl;
                return;
            }
        }
        cout << 1 << endl;
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