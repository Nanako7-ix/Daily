/**
 * Author: Nanako7_ix
 * Created: 2025/04/12 20:49:55
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
    int d = 0;
    array<pair<int, vector<vector<int>>>, 2> G {};

    auto read = [&](int op) {
        auto& [n, adj] = G[op];
        cin >> n;
        adj.assign(n + 1, {});
        for(int i = 1; i < n; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    };
    read(0), read(1);

    auto work = [&](int op) {
        auto& [n, adj] = G[op];
        vector<array<int, 2>> dp(n + 1);
        auto dfs1 = [&](auto&& dfs, int u, int fa) -> void {
            for(auto v : adj[u]) {
                if(v == fa) continue;
                dfs(dfs, v, u);
                int get = dp[v][0] + 1;
                if(get > dp[u][0]) {
                    dp[u][1] = dp[u][0];
                    dp[u][0] = get;
                } else if(get > dp[u][1]) {
                    dp[u][1] = get;
                }
            }
        };
        auto dfs2 = [&](auto&& dfs, int u, int fa) -> void {
            for(auto v : adj[u]) {
                if(v == fa) continue;
                int get = dp[u][0] == dp[v][0] + 1 ? dp[u][1] + 1 : dp[u][0] + 1;
                if(get > dp[v][0]) {
                    dp[v][1] = dp[v][0];
                    dp[v][0] = get;
                } else if(get > dp[v][1]) {
                    dp[v][1] = get;
                }
                dfs(dfs, v, u);
            }
        };
        dfs1(dfs1, 1, 0);
        dfs2(dfs2, 1, 0);

        vector<int> res(n + 1);
        for(int i = 1; i <= n; ++i) {
            res[i] = dp[i][0];
            d = max(d, res[i]);
        }
        return res;
    };

    i64 n = G[0].first, m = G[1].first;
    array<vector<int>, 2> dp { work(0), work(1) };
    vector<i64> cnt(m + 1), sum(m + 1);
    for(int i = 1; i <= m; ++i) {
        cnt[dp[1][i]]++;
        sum[dp[1][i]] += dp[1][i];
    }
    for(int i = 1; i <= m; ++i) {
        cnt[i] += cnt[i - 1];
        sum[i] += sum[i - 1];
    }

    i64 ans = 0;
    for(int i = 1; i <= n; ++i) {
        i64 l = dp[0][i];
        // 没判上界，警钟敲烂!!!
        if (d - l - 1 >= m) {
            ans += cnt[m] * d;
        } else {
            ans += (d - l - 1 >= 0 ? cnt[min(d - l - 1, m)] : 0) * d;
            ans += (sum[m] - (d - l - 1 >= 0 ? sum[min(d - l - 1, m)] : 0)) + (cnt[m] - (d - l - 1 >= 0 ? cnt[d - l - 1] : 0)) * (l + 1);
        }
    }
    cout << ans << endl;
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