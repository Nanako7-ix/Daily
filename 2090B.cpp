// Author: Nanako7_ix
// Created: 2025/03/24 22:11:40
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
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n + 1, vector<int> (m + 1));
    for(int i = 1; i <= n; ++i) {
        string s;
        cin >> s;
        for(int j = 1; j <= m; ++j) {
            a[i][j] = s[j - 1] ^ 48;
        }
    }
    for(int i = 1; i <= m; ++i) {
        a[0][i] = 1;
    }
    for(int i = 1; i <= n; ++i) {
        a[i][0] = 2;
    }
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            if(a[i][j] == 0) continue;
            a[i][j] = 0;
            a[i][j] |= a[i - 1][j] & 1;
            a[i][j] |= a[i][j - 1] & 2;
            if(a[i][j] == 0) {
                cout << "No\n";
                return;
            }
        }
    }
    cout << "Yes\n";
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}