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
    
    auto insert = [](array<int, 2>& a, int v) {
        if(v > a[0]) {
            a[1] = a[0], a[0] = v;
        } else if(v > a[1]) {
            a[1] = v;
        }
    };
    auto add = [](array<int, 2>& a, int v) {
        if(v == a[0]) a[0]++;
        else if(v == a[1]) a[1]++;
    };
    auto del = [](array<int, 2>& a, int v) {
        if(v == a[0]) a[0]--;
        if(a[0] < a[1]) swap(a[0], a[1]);
    };

    int ans = inf, p = -1;
    vector<int> deg(n + 1);
    vector<array<int, 2>> dp(n + 1);
    auto dfs1 = [&](auto &&dfs, int u, int fa) -> void {
        dp[u] = {0, 0};
        for(auto v : adj[u]) {
            if(v == fa) continue;
            dfs(dfs, v, u);
            deg[u]++;
            insert(dp[u], dp[v][0]);
        }
        insert(dp[u], deg[u]);
    };
    auto dfs2 = [&](auto &&dfs, int u, int fa) -> void {
        if(dp[u][0] < ans || (dp[u][0] == ans && u < p)) {
            ans = dp[u][0], p = u;
        }
        del(dp[u], adj[u].size());
        for(int v : adj[u]) {
            if(v == fa) continue;
            add(dp[v], deg[v]);
            insert(dp[v], dp[u][0]);
            dfs(dfs, v, u);
        }
    };
    dfs1(dfs1, 1, 0), dfs2(dfs2, 1, 0);

    cout << ans << ' ' << p << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}