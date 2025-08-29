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
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1), col(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> col[i];
    }

    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    if (*max_element(col.begin() + 1, col.end()) == 0) {
        cout << "0\n";
        for (int i = 1; i <= n; ++i) {
            cout << 1 << " \n"[i == n];
        }
        return;
    }

    i64 ans = 0;
    [&](this auto&& dfs, int u, int fa) -> set<int> {
        int ok = 1;
        set<int> s;
        for (auto v : adj[u]) {
            if (v == fa) continue;
            auto t = dfs(v, u);
            if (col[v] == 0) continue;
            if (s.size() < t.size()) {
                swap(s, t);
            }
            for (auto c : t) {
                if (!s.contains(c)) {
                    s.insert(c);
                } else if (col[u] == 0) {
                    col[u] = c;
                } else if (col[u] != c) {
                    ok = 0;
                }
            }
        }
        if (col[u] == 0) {
            col[u] = *s.begin();
        }
        if (ok == 0) {
            ans += a[u];
        }
        s.insert(col[u]);
        return s;
    } (1, 0);

    [&](this auto&& dfs, int u, int fa) -> void {
        for (auto v : adj[u]) {
            if (v == fa) continue;
            if (col[v] == 0) {
                col[v] = col[u];
            }
            dfs(v, u);
        }
    } (1, 0);

    cout << ans << "\n";
    for (int i = 1; i <= n; ++i) {
        cout << col[i] << " \n"[i == n];
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