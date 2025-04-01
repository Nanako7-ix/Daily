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
    vector<int> a(n + 1);
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for(int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<i64> siz(n + 1), dp(n + 1);
    [&](this auto &&dfs, int u, int fa) -> void {
        siz[u] = 1;
        for(auto v: adj[u]) {
            if(v == fa) continue;
            dfs(v, u);
            siz[u] += siz[v];
            dp[u] += dp[v] + (a[u] ^ a[v]) * siz[v];
        }
    } (1, 0);
    
    [&](this auto &&dfs, int u, int fa) -> void {
        for(auto v : adj[u]) {
            if(v == fa) continue;
            dp[v] = dp[u] + (a[u] ^ a[v]) * (siz[1] - 2 * siz[v]);
            dfs(v, u);
        }
    } (1, 0);
    
    for(int i = 1; i <= n; ++i) {
        cout << dp[i] << " \n"[i == n];
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}