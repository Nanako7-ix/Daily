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
    vector<int> col(n + 1), ans(n + 1);
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int u = 1; u <= n; ++u) {
        cin >> col[u];
    }

    auto dfs = [&](auto&& dfs, int u, int fa) -> set<int> {
        set<int> s {col[u]};
        for (auto v : adj[u]) {
            if (v == fa) continue;
            auto t = dfs(dfs, v, u);
            if (t.size() > s.size()) {
                swap(s, t);
            }
            for (auto x : t) {
                s.insert(x);
            }
        }
        ans[u] = s.size();
        return s;
    };
    dfs(dfs, 1, 0);
    
    int q; cin >> q;
    for (int i = 1; i <= n; ++i) {
        int u; cin >> u;
        cout << ans[u] << "\n";
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