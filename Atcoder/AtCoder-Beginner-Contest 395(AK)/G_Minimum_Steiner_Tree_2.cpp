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
    int n, k;
    cin >> n >> k;
    vector<vector<i64>> a(n + 1, vector<i64> (n + 1));
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            cin >> a[i][j];
        }
    }

    vector<vector<i64>> ans(n + 1, vector<i64> (n + 1));
    for(int x = k + 1; x <= n; ++x) {
        vector<vector<i64>> dp(n + 1, vector<i64> (1 << k + 1, INF));
        for(int i = 1; i <= k; ++i) {
            dp[i][1 << (i - 1)] = 0;
        }
        dp[x][1 << k] = 0;
    
        for(int s = 1; s < (1 << (k + 1)); ++s) {
            priority_queue<array<i64, 2>, vector<array<i64, 2>>, greater<array<i64, 2>>> q;
            for(int i = 1; i <= n; ++i) {
                for(int t = (s - 1) & s; t; t = (t - 1) & s) {
                    dp[i][s] = min(dp[i][s], dp[i][s ^ t] + dp[i][t]);
                }
                q.push({dp[i][s], i});
            }
            while(!q.empty()) {
                auto [d, u] = q.top();
                q.pop();
                if(d > dp[u][s]) continue;
                for(int v = 1; v <= n; ++v) {
                    if(v == u) continue;
                    i64 w = a[u][v];
                    if(dp[u][s] + w < dp[v][s]) {
                        dp[v][s] = dp[u][s] + w;
                        q.push({dp[v][s], v});
                    }
                }
            }
        }
        
        for(int y = x + 1; y <= n; ++y) {
            ans[x][y] = dp[y][(1 << k + 1) - 1];
        }
    }

    int q; cin >> q;
    while(q--) {
        int x, y;
        cin >> x >> y;
        if(x > y) swap(x, y);
        cout << ans[x][y] << endl;
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}