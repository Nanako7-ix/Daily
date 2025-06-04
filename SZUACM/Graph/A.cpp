/**
 * Author:  Thephix
 * Created: 2025/06/04 16:50:05
 */
#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using i128 = __int128;
using u128 = unsigned __int128;
using f64 = double;
using f128 = __float128;
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1), dp(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    dp[1] = a[1];
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    cout << [&](this auto&& dfs, int u, int fa) -> int {
        int cnt = 0, son = 0;
        for (auto v : adj[u]) {
            if (v == fa) continue;
            son++;
            if (a[v] == 1) {
                a[v] += a[u];
            }
            dp[v] = max(a[v], dp[u]);
            cnt += dfs(v, u);
        }
        if (son == 0 && dp[u] <= m) cnt++;
        return cnt;
    } (1, 0) << "\n";
}

signed main() {
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int T = 1;
    // std::cin >> T;

    while (T--) {
        solve ();
    }

    return 0;
}