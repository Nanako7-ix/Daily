#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
using i64 = long long;

constexpr i64 mod = 998244353;
struct Mod {
    i64 x; Mod(i64 x = 0) :x(x% mod) {}
    operator i64() const { return x; }
    Mod operator+(const i64& v) const { return x + v; }
    Mod operator*(const i64& v) const { return x * v; }
    Mod operator-(const i64& v) const { return x - v + mod; }
    Mod& operator+=(const i64& v) { return *this = x + v; }
    Mod& operator*=(const i64& v) { return *this = x * v; }
    Mod& operator-=(const i64& v) { return *this = x - v + mod; }
};

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<array<int, 2>> E(n);
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; ++i) {
        auto& [u, v] = E[i];
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> dep(n + 1);
    vector fa(n + 1, vector<array<int, 2>>(__lg(n) + 1));
    auto dfs = [&](auto&& dfs, int u) -> void {
        for (auto& v : adj[u]) {
            if (v == fa[u][0][0]) continue;
            fa[v][0][0] = u;
            dep[v] = dep[u] + 1;
            dfs(dfs, v);
        }
    };
    dfs(dfs, 1);


    for (int i = 0; i < m; ++i) {
        int p; cin >> p;
        auto [u, v] = E[p];
        if (fa[u][0][0] != v) {
            swap(u, v);
        }
        fa[u][0] = { v, 1 << (p - 1) };
    }
    for (int i = 1; i <= __lg(n); ++i) {
        for (int u = 1; u <= n; ++u) {
            fa[u][i][0] = fa[fa[u][i - 1][0]][i - 1][0];
            fa[u][i][1] = fa[u][i - 1][1] | fa[fa[u][i - 1][0]][i - 1][1];
        }
    }

    auto lca = [&](int u, int v) -> int {
        int res = 0;
        if (dep[u] < dep[v]) swap(u, v);
        while (dep[u] > dep[v]) {
            res |= fa[u][__lg(dep[u] - dep[v])][1];
            u = fa[u][__lg(dep[u] - dep[v])][0];
        }

        if (u == v) return res;
        for (int i = __lg(dep[u]); i >= 0; --i) {
            auto& [xf, xw] = fa[u][i];
            auto& [yf, yw] = fa[v][i];
            if (xf == yf) continue;
            res |= xw | yw;
            u = xf, v = yf;
        }
        return res | fa[u][0][1] | fa[v][0][1];
    };

    vector<int> a(k);
    map<int, int> cnt;
    for (auto& s : a) {
        int u, v; cin >> u >> v;
        s = lca(u, v);
        cnt[s]++;
    }

    cerr << cnt.size() << "\n";

    vector<int> Dep(1 << m, -1);
    vector<Mod> Cnt(1 << m);

}
int main() {
    cin.tie(nullptr)->sync_with_stdio(0);
    solve();
    return 0;
}