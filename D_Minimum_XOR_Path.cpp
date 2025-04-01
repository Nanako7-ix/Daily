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
    vector<vector<array<i64, 2>>> adj(n + 1);
    for(int i = 1; i <= m; ++i) {
        i64 u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    i64 ans = 1LL << 60;
    vector<int> vis(n + 1);
    vis[1] = 1;
    auto dfs = [&](auto&& dfs, int u, i64 sum) -> void {
        if(u == n) {
            ans = min(ans, sum);
            return;
        }
        for(auto [v, w] : adj[u]) {
            if(vis[v]) continue;
            vis[v] = 1;
            dfs(dfs, v, sum ^ w);
            vis[v] = 0;
        }
    };
    dfs(dfs, 1, 0);
    cout << ans << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}