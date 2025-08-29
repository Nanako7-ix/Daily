#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr i64 inf = 1E15;

void Thephix() {
    int n, m;
    cin >> n >> m;
    vector<vector<i64>> dp(n + 1, vector<i64> (n + 1, inf));
    for (int i = 1; i <= n; ++i) {
        dp[i][i] = 0;
    }
    for (int i = 1; i <= m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        dp[u][v] = min<i64> (dp[u][v], w);
        dp[v][u] = min<i64> (dp[v][u], w);
    }
    int k, W;
    cin >> k >> W;
    vector<int> fly(k + 1);
    for (int i = 1; i <= k; ++i) {
        cin >> fly[i];
        for (int j = 1; j < i; ++j) {
            int u = fly[i];
            int v = fly[j];
            dp[u][v] = min<i64> (dp[u][v], W);
            dp[v][u] = min<i64> (dp[v][u], W);
        }
    }

    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
            }
        }
    }

    i64 ans = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (dp[i][j] == inf) continue;
            ans += dp[i][j];
        }
    }

    auto update = [&](i64& val, i64 now) {
        if (val > now) {
            if (val != inf) {
                ans -= val;
            }
            ans += (val = now);
        }
    };
    
    int q;
    cin >> q;
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int u, v, w;
            cin >> u >> v >> w;
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) {
                    i64 now = min(
                        dp[i][u] + w + dp[v][j],
                        dp[i][v] + w + dp[u][j]
                    );
                    update(dp[i][j], now);
                }
            }
        } else if (op == 2) {
            int p;
            cin >> p;
            fly.push_back(p);
            for (int i = 1; i <= k; ++i) {
                int u = fly[i];
                for (int v = 1; v <= n; ++v) {
                    update(dp[v][p], dp[v][u] + W);
                    update(dp[p][v], dp[v][u] + W);
                }
            }
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) {
                    update(dp[i][j], dp[i][p] + dp[p][j]);
                }
            }
            k += 1;
        } else {
            cout << ans << "\n";
        }
    }
}

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T = 1;
    // cin >> T;

    while (T--) {
        Thephix();
    }

    return 0;
}