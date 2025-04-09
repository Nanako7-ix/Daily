// Author: Nanako7_ix
// Created: 2025/04/09 21:03:10
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
    int n, m;
    cin >> n >> m;
    vector<string> a(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    vector<int> vis(n + 1);
    int ans = 0;
    for(int i = 1; i <= m; ++i) {
        int res = 0;
        for(int j = 1; j <= n; ++j) {
            string s;
            cin >> s;
            if(s == a[j]) {
                vis[j] = 1, res++;
            }
        }
        ans = max(ans, res);
    }
    if(accumulate(vis.begin() + 1, vis.end(), 0LL) != n) {
        cout << "-1\n";
    } else {
        cout << 3 * n - 2 * ans << endl;
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