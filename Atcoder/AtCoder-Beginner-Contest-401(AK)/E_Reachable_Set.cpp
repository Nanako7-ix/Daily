/**
 * Author: Nanako7_ix
 * Created: 2025/04/13 01:17:37
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
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> dp(n + 1, inf), vis(n + 1);
    priority_queue<array<int, 2>, vector<array<int, 2>>, greater<array<int, 2>>> q;
    q.push({dp[1] = 1, 1});
    while (!q.empty()) {
        auto [_, u] = q.top();
        q.pop();
        if(vis[u]) continue;
        vis[u] = 1;
        for(auto v : adj[u]) {
            if(dp[v] > max({u, v, _})) {
                q.push({dp[v] = max({u, v, _}), v});
            }
        }
    }

    int need = 0;
    set<int> S;
    for(int u = 1; u <= n; ++u) {
        S.erase(u);
        for(auto v : adj[u]) {
            if(v > u) S.insert(v);
        }
        need = max(need, dp[u]);

        cout << (u >= need ? (int) S.size() : -1) << endl;
    }
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
    
    int T = 1;
    // cin >> T;
    
    while (T--) {
        solve();
    }
    
    return 0;
}