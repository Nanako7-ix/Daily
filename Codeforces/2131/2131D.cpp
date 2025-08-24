#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

void Thephix() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    if (n == 2) {
        cout << "0\n";
        return;
    }

    int ans = 0, res = 0;
    for (int u = 1; u <= n; ++u) {
        if (adj[u].size() == 1) {
            ans++;
        }
        int cnt = 0;
        for (auto v : adj[u]) {
            if (adj[v].size() == 1) {
                cnt++;
            }
        }
        res = max(res, cnt);
    }
    if (ans == n - 1) {
        cout << 0 << "\n";
    } else {
        cout << ans - res << "\n";
    }
}

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T = 1;
    cin >> T;

    while (T--) {
        Thephix();
    }

    return 0;
}