/**
 * Author:  Nanako7_ix
 * Created: 2025/05/05 23:48:15
 * 好想和 めぐる 一起打 xcpc 啊
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
    int n;
    cin >> n;
    vector<set<int>> adj(n + 1);
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].insert(v);
        adj[v].insert(u);
    }

    vector<int> a;
    vector<array<int, 2>> dp(n + 1);
    vector<int> fa(n + 1);

    auto dfs = [&](this auto&& dfs, int u) -> int {
        dp[u] = {0, u};
        for (auto v : adj[u]) {
            if (v == fa[u]) continue;
            fa[v] = u;
            dfs(v);
            dp[u] = max(dp[u], dp[v]);
        }
        dp[u][0]++;
        return u;
    };

    set<array<int, 4>, greater<array<int, 4>>> tr;
    auto insert = [&](int u) -> void {
        fa[u] = 0;
        dfs(u);
        u = dp[u][1];
        fa[u] = 0;
        dfs(u);
        tr.insert({dp[u][0], max(u, dp[u][1]), min(u, dp[u][1]), u});
    };

    insert(1);
    while (!tr.empty()) {
        auto it = tr.begin();
        auto [d, u, v, rt] = *it;
        tr.erase(it);
        a.push_back(d), a.push_back(u), a.push_back(v);

        int x = u ^ v ^ rt;
        fa[rt] = 0;
        while (x != 0) {
            int nxt = fa[x];

            for (auto v : adj[x]) {
                adj[v].erase(x);
                if (v == nxt) continue;
                insert(v);
            }
            x = nxt;
        }
    }

    for (auto x : a) cout << x << ' ';
    cout << endl;
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
    
    int T = 1;
    cin >> T;
    
    while (T--) {
        solve();
    }
    
    return 0;
}