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
    vector<vector<int>> adj(n + 1);
    vector<i64> p(n + 1), dp(n + 1);
    for(int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    auto dfs = [&](auto &&dfs, int u) -> void {
        for(auto v : adj[u]) {
            if(v == p[u]) continue;
            p[v] = u;
            dfs(dfs, v);
            dp[u] += dp[v] + abs(u - v);
        }
    };
    dfs(dfs, 1);
    
    i64 ans = INF;
    for(int i = 2; i <= n; ++i) {
        ans = min(ans, abs(dp[1] - 2 * dp[i] - abs(i - p[i])));
    }
    cout << ans << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}