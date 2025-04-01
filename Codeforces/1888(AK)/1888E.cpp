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
    int n, t;
    cin >> n >> t;
    map<array<int, 2>, vector<int>> mp;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i <= t; ++i) {
        int m; cin >> m;
        for(int j = 1; j <= m; ++j) {
            int u, v;
            cin >> u >> v;
            if(!mp.contains({u, v})) {
                adj[u].push_back(v);
                adj[v].push_back(u);
            }
            mp[{u, v}].push_back(i);
            mp[{v, u}].push_back(i);
        }
    }

    int k; cin >> k;
    vector<int> a(k + 1);
    vector<vector<int>> p(t + 1);
    for(int i = 1; i <= k; ++i) {
        cin >> a[i];
        p[a[i]].push_back(i);
    }

    auto w = [&](int u, int v, int t) -> int {
        int ans = inf;
        for(auto x : mp[{u, v}]) {
            auto it = lower_bound(p[x].begin(), p[x].end(), t);
            if(it != p[x].end()) {
                ans = min(ans, *it);
            }
        }
        return ans;
    };

    vector<int> dp(n + 1, inf), vis(n + 1);
    priority_queue<array<int, 2>, vector<array<int, 2>>, greater<array<int, 2>>> q;
    dp[1] = 0;
    q.push({0, 1});
    while(!q.empty()) {
        auto [_, u] = q.top();
        q.pop();
        if(vis[u]) continue;
        vis[u] = 1;
        for(auto v : adj[u]) {
            int dis = w(u, v, dp[u] + 1);
            if(dp[v] > dis) {
                dp[v] = dis;
                q.push({dis, v});
            }
        }
    }
    if(dp[n] == inf) {
        cout << -1 << endl;
    } else {
        cout << dp[n] << endl;
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}