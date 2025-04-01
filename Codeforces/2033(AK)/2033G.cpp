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

    vector<int> dep(n + 1);
    vector fa(n + 1, vector<array<int, 2>> (20));
    vector<array<int, 2>> dp(n + 1);

    [&](this auto &&dfs, int u) -> void {
        dp[u] = {};
        for(auto v : adj[u]) {
            if(v == fa[u][0][0]) continue;
            fa[v][0][0] = u;
            dep[v] = dep[u] + 1;
            dfs(v);
            if(dp[v][0] + 1 > dp[u][0]) {
                dp[u][1] = dp[u][0];
                dp[u][0] = dp[v][0] + 1;
            } else if(dp[v][0] + 1 > dp[u][1]) {
                dp[u][1] = dp[v][0] + 1;
            }
        }
    } (1);

    for(int u = 2; u <= n; ++u) {
        if(dp[u][0] + 1 == dp[fa[u][0][0]][0]) {
            fa[u][0][1] = dp[fa[u][0][0]][1] + 1;
        } else {
            fa[u][0][1] = dp[fa[u][0][0]][0] + 1;
        }
    }

    for(int k = 1; k < 18; ++k) {
        for(int u = 1; u <= n; ++u) {
            int nxt = fa[u][k - 1][0];
            fa[u][k][0] = fa[nxt][k - 1][0];
            if(fa[u][k][0] == 0) continue;
            fa[u][k][1] = max(fa[u][k - 1][1], (1 << (k - 1)) + fa[nxt][k - 1][1]);
        }
    }

    int q; cin >> q;
    while(q--) {
        int u, k;
        cin >> u >> k;
        k = min(k, dep[u]);
        int ans = dp[u][0];
        for(int i = 0, v = u; i < 18; ++i) {
            if(k >> i & 1) {
                ans = max(ans, fa[v][i][1] - dep[v] + dep[u]);
                v = fa[v][i][0];
            }
        }
        cout << ans << " \n"[!q];
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}