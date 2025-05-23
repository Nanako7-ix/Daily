// Author: Nanako7_ix
// Created: 2025/03/30 16:35:37
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
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    if(a[n] == 0) {
        for(int i = 1; i <= n; ++i) {
            cout << i << ' ';
        }
        cout << n + 1 << endl;
        return;
    }
    if(a[1] == 1) {
        cout << n + 1 << ' ';
        for(int i = 1; i <= n; ++i) {
            cout << i << " \n"[i == n];
        }
        return;
    }
    for(int i = 1; i < n; ++i) {
        if(a[i] == 0 && a[i + 1] == 1) {
            for(int j = 1; j <= i; ++j) {
                cout << j << ' ';
            }
            cout << n + 1 << endl;
            for(int j = i + 1; j <= n; ++j) {
                cout << j << " \n"[j == n];
            }
            return;
        }
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}