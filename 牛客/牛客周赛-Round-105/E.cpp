#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr i64 Mod = 998244353;

void Thephix() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    vector<vector<int>> adj(n + 1);
    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    i64 ans = 0;
    for (int u = 1; u <= n; ++u) {
        array<array<i64, 2>, 30> cnt {};
        for (auto v : adj[u]) {
            for (int i = 0; i < 30; ++i) {
                int x = (a[u] ^ a[v]) >> i & 1;
                ans += (cnt[i][x ^ 1] << i) % Mod;
                ans %= Mod;
                cnt[i][a[v] >> i & 1]++;
            }
        }
    }
    cout << ans << "\n";
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