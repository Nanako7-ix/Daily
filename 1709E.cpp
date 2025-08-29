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
    vector<int> a(n + 1);
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int ans = 0;
    [&](this auto&& dfs, int u, int fa) -> pair<set<int>, int> {
        int ok = 1, tag_s = a[u];
        set<int> s { 0 };
        for (auto v : adj[u]) {
            if (v == fa) continue;
            auto [t, tag_t] = dfs(v, u);
            tag_t ^= a[u];
            if (t.size() > s.size()) {
                swap(s, t);
                swap(tag_s, tag_t);
            }
            for (auto x : t) {
                ok &= !s.contains(x ^ tag_s ^ tag_t ^ a[u]);
            }
            for (auto x : t) {
                s.insert(x ^ tag_s ^ tag_t);
            }
        }
        if (ok == 0) {
            ans++;
            s.clear(), tag_s = 0;
        }
        return pair {move(s), tag_s};
    } (1, 0);

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