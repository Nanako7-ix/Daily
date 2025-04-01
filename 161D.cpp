// Author: Nanako7_ix
// Created: 2025/03/23 22:55:52
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
    int n, k;
    cin >> n >> k;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    i64 ans = 0;
    vector<vector<int>> dp(n + 1, vector<int> (k + 1));
    [&](this auto&& dfs, int u, int fa) -> void {
        dp[u][0] = 1;
        for(auto v : adj[u]) {
            if(v == fa) continue;
            dfs(v, u);
            for(int i = 0; i < k; ++i) {
                ans += dp[u][k - i - 1] * dp[v][i];
            }
            for(int i = 1; i <= k; ++i) {
                dp[u][i] += dp[v][i - 1];
            }
        }
    } (1, 0);

    cout << ans << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}