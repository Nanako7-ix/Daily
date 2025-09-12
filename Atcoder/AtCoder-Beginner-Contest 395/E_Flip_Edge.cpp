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
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<array<int, 2>>> adj(n + 1);
    for(int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back({v, 0});
        adj[v].push_back({u, 1});
    }

    vector<array<i64, 2>> dp(n + 1, {INF, INF}), vis(n + 1, {0, 0});
    priority_queue<array<i64, 3>, vector<array<i64, 3>>, greater<array<i64, 3>>> q;
    q.push({dp[1][0] = 0, 1, 0});
    while(!q.empty()) {
        auto [_, u, op] = q.top();
        q.pop();
        if(vis[u][op]) continue;
        vis[u][op] = 1;
        for(auto [v, x] : adj[u]) {
            if(x != op) continue;
            if(dp[v][op] > dp[u][op] + 1) {
                dp[v][op] = dp[u][op] + 1;
                q.push({dp[v][op], v, op});
            }
        }
        if(dp[u][op ^ 1] > dp[u][op] + k) {
            dp[u][op ^ 1] = dp[u][op] + k;
            q.push({dp[u][op ^ 1], u, op ^ 1});
        }
    }
    
    cout << min(dp[n][0], dp[n][1]) << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}