// Author: Nanako7_ix
// Created: 2025/04/03 23:01:15
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
    int n, ans = 0;
    cin >> n;
    vector<int> p(n + 1), vis(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> p[i];
    }
    for(int i = 1; i <= n; ++i) {
        int x; cin >> x;
        if(!vis[x]) {
            for(int u = x; !vis[u]; vis[u] = 1, u = p[u]) {
                ans++;
            }
        }
        cout << ans << " \n"[i == n];
    }
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}