// Author: Nanako7_ix
// Created: 2025/03/30 19:40:41
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
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
    int n, x, y;
    cin >> n >> x >> y;
    vector<int> a(n + 1);
    for(int i = 0; i < 31; ++i) {
        int f = x >> i & 1;
        int g = y >> i & 1;

        if(f == 0 && g == 0) {
            continue;
        } else if(f == 0 && g == 1 || (f == 1 && g == 0 && n == 1)) {
            cout << "NO\n";
            return;
        }
        
        if(f == 1 && g == 0) {
            if(n & 1) {
                if(a[1] == 0) {
                    for(int j = 1; j < n; ++j) {
                        a[j] ^= 1 << i;
                    }
                } else {
                    for(int j = 2; j <= n; ++j) {
                        a[j] ^= 1 << i;
                    }
                }
            } else {
                for(int j = 1; j <= n; ++j) {
                    a[j] ^= 1 << i;
                }
            }
        } else {
            if(n & 1) {
                for(int j = 1; j <= n; ++j) {
                    a[j] ^= 1 << i;
                }
            } else if(a[1] == 0) {
                for(int j = 1; j < n; ++j) {
                    a[j] ^= 1 << i;
                }
            } else {
                for(int j = 2; j <= n; ++j) {
                    a[j] ^= 1 << i;
                }
            }
        }
    }

    if(*min_element(a.begin() + 1, a.end()) == 0) {
        cout << "NO\n";
        return;
    }

    cout << "YES\n";
    for(int i = 1; i <= n; ++i) {
        cout << a[i] << " \n"[i == n];
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}