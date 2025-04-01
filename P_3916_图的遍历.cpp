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
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[v].push_back(u);
    }

    vector<int> ans(n + 1);
    iota(ans.begin(), ans.end(), 0);
    for(int i = n; i >= 1; --i) {
        auto dfs = [&](auto&& dfs, int u) -> void {
            ans[u] = ans[i];
            for(auto v : adj[u]) {
                if(ans[v] < ans[u]) {
                    dfs(dfs, v);
                }
            }
        };
        dfs(dfs, i);
    }
    for(int i = 1; i <= n; ++i) {
        cout << ans[i] << ' ';
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}