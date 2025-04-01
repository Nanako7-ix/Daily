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
    for(int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<array<array<int, 2>, 2>> dp(n + 1);
    [&](this auto &&dfs, int u, int fa) -> void {
        dp[u] = {array<int, 2>{0, u}, array<int, 2>{0, u}};
        for(auto v : adj[u]) {
            if(v == fa) continue;
            dfs(v, u);
            auto get = dp[v][0];
            get[0]++;
            if(get > dp[u][0]) {
                dp[u][1] = dp[u][0];
                dp[u][0] = get;
            } else if(get > dp[u][1]) {
                dp[u][1] = get;
            }
        }
    } (1, 0);

    int ans = 0, x, y;
    for(int i = 1; i <= n; ++i) {
        auto [u, v] = dp[i];
        if(u[0] + v[0] > ans) {
            ans = u[0] + v[0];
            x = u[1], y = v[1];
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