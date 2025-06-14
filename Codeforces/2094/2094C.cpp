/**
 * Author: Nanako7_ix
 * Created: 2025/04/14 00:14:44
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
    vector<int> p(2 * n + 1), vis(2 * n + 1);
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            int x; cin >> x;
            vis[p[i + j] = x] = 1;
        }
    }
    for(int i = 1; i <= 2 * n; ++i) {
        if(vis[i] == 0) p[1] = i;
    }
    for(int i = 1; i <= 2 * n; ++i) {
        cout << p[i] << " \n"[i == 2 * n];
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