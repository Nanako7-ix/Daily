#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

constexpr i64 Mod = 998244353, g = 3, gi = 332748118, p = 998244353;

vector<i64> Convolution(vector<i64> a, vector<i64> b) {
    int n = a.size(), m = b.size();
    vector<i64> ans(n + m - 1);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            ans[i + j] += a[i] * b[j] % Mod;
            ans[i + j] %= Mod;
        }
    }

    return ans;
}

void solve () {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<vector<i64>> dp(n + 1);
    auto dfs = [&](auto&& dfs, int u, int fa) -> void {
        dp[u].assign(1, 1);
        for (auto v : adj[u]) {
            if (v == fa) continue;
            dfs(dfs, v, u);
            dp[u] = Convolution(dp[u], dp[v]);
        }

        while (dp[u].back() == 0) dp[u].pop_back();
        int size = dp[u].size();

        dp[u].push_back(0);
        vector<i64> ndp(size + 1);
        // u 是诚实者
        if (a[u] != 0 && a[u] <= size) {
            ndp[a[u]] = dp[u][a[u] - 1];
        }
        // u 是说谎者
        for (int i = 0; i < size; ++i) {
            if (i != a[u]) ndp[i] = dp[u][i];
        }

        swap(dp[u], ndp);
    };

    dfs(dfs, 1, 0);
    i64 sum = 0;
    for (int i = 0; i < (int) dp[1].size(); ++i) {
        (sum += dp[1][i]) %= Mod;
    }
    cout << sum << "\n";
}

int main () {
    cin.tie(nullptr), cout.tie(nullptr) -> sync_with_stdio(false);
    int T = 1;
    cin >> T;
    while (T--) {
        solve ();
    }
}