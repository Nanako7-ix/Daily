/**
 * Author: Nanako7_ix
 * Created: 2025/04/17 14:06:38
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
    int n, k, x;
    cin >> n >> k >> x;
    if (x != 1) {
        cout << "YES\n";
        cout << n << endl;
        for(int i = 1; i <= n; ++i) {
            cout << 1 << " \n"[i == n];
        }
    } else {
        if (n & 1) {
            if (k < 3) {
                cout << "NO\n";
            } else {
                n -= 3;
                if (n < 0) {
                    cout << "NO\n";
                } else {
                    cout << "YES\n";
                    cout << 1 + n / 2 << endl;
                    cout << 3 << ' ';
                    for (int i = 1; i <= n / 2; ++i) {
                        cout << 2 << " \n"[i == n / 2];
                    }
                }
            }
        } else {
            if (k < 2) {
                cout << "NO\n";
            } else {
                cout << "YES\n";
                cout << n / 2 << endl;
                for (int i = 1; i <= n / 2; ++i) {
                    cout << 2 << " \n"[i == n / 2];
                }
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