/**
 * Author: Nanako7_ix
 * Created: 2025/04/18 19:08:27
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
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> a(n + 1);
    for (int i = 1; i <= m; ++i) {
        int x; cin >> x;
        a[x] = 1;
    }

    vector<array<int, 2>> ans;

    auto dfs = [&](auto dfs, int u, int fa) -> int {
        vector<array<int, 2>> res;
        for (auto v : adj[u]) {
            if (v == fa) continue;
            if (dfs(dfs, v, u)) {
                res.push_back({u, v});
            }
        }
        if (a[u]) {
            for (auto x : res) {
                ans.push_back(x);
            }
            return 1;
        } else if (!res.empty()) {
            res.pop_back();
            for (auto x : res) {
                ans.push_back(x);
            }
            return 1;
        } else {
            return 0;
        }
    };

    dfs(dfs, 1, 0);
    cout << ans.size() << endl;
    for (auto [u, v] : ans) {
        cout << u << ' ' << v << endl;
    }
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
    
    int T = 1;
    // cin >> T;
    
    while (T--) {
        solve();
    }
    
    return 0;
}