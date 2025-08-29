#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

struct DSU {
    vector<int> fa, siz;
    DSU (int n) : fa(n + 1), siz(n + 1, 1) {
        iota(fa.begin(), fa.end(), 0);
    }
    int find(int u) {
        if (fa[u] == u) return u;
        return fa[u] = find(fa[u]);
    }
    bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        fa[x] = y;
        siz[y] += siz[x];
        return true;
    }
};

constexpr i64 Mod = 1000000007;
constexpr int N = 1E6;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

i64 val[N], sum[N], phi[N], tag[N];
int siz[N], ls[N], rs[N], tot = 0;

int Node(i64 x) {
    tot++;
    val[tot] = sum[tot] = x;
    siz[tot] = 1;
    ls[tot] = rs[tot] = 0;
    phi[tot] = rng();
    tag[tot] = -1;
    return tot;
}

void push(int u) {
    if (tag[u] == -1) return;
    if (ls[u]) {
        tag[ls[u]] = tag[u];
        val[ls[u]] = tag[u];
        sum[ls[u]] = tag[u] * siz[ls[u]] % Mod;
    }
    if (rs[u]) {
        tag[rs[u]] = tag[u];
        val[rs[u]] = tag[u];
        sum[rs[u]] = tag[u] * siz[rs[u]] % Mod;
    }
    tag[u] = -1;
}

void pull(int u) {
    siz[u] = siz[ls[u]] + siz[rs[u]] + 1;
    sum[u] = (sum[ls[u]] + sum[rs[u]] + val[u]) % Mod;
}

void split(int u, i64 k, int& x, int& y) {
    if (!(x = y = u)) return;
    push(u);
    if (val[u] <= k) {
        split(rs[u], k, rs[u], y);
    } else {
        split(ls[u], k, x, ls[u]);
    }
    pull(u);
}

[[nodiscard]] int merge(int x, int y) {
    if (!x || !y) return x | y;
    push(x), push(y);
    if (phi[x] < phi[y]) {
        rs[x] = merge(rs[x], y);
        pull(x);
        return x;
    } else {
        ls[y] = merge(x, ls[y]);
        pull(y);
        return y;
    }
}

void Thephix() {
    tot = 0;

    i64 n, m, k;
    cin >> n >> m >> k;
    vector<array<i64, 3>> E(m + 1);
    for (int i = 1; i <= m; ++i) {
        auto& [w, u, v] = E[i];
        cin >> u >> v >> w;
    }

    E[0];
    
    sort(E.begin() + 1, E.end());
    int tot = n;
    DSU dsu(n);
    vector<vector<array<i64, 2>>> adj(n + 1);
    for (int i = 1; i <= m; ++i) {
        auto& [w, u, v] = E[i];
        if (dsu.merge(u, v)) {
            tot--;
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
    }

    if (tot > 2) {
        cout << 0 << "\n";
        return;
    }
    
    if (tot == 2) {
        set<int> S;
        for (int i = 1; i <= n; ++i) {
            S.insert(dsu.find(i));
        }
        int x = *S.begin(), y = *S.rbegin();
        cout << (1LL * dsu.siz[x] * dsu.siz[y]) % Mod * k % Mod << "\n";
        return;
    }

    i64 ans = 0;
    vector<int> dep(n + 1);
    vector<vector<array<i64, 2>>> fa(n + 1, vector<array<i64, 2>> (__lg(n) + 1));
    auto dfs = [&](auto&& dfs, int u) -> int {
        int s = Node(0);
        for (auto& [v, w] : adj[u]) {
            if (v == fa[u][0][0]) {
                continue;
            }
            fa[v][0] = { u, w };
            dep[v] = dep[u] + 1;
            int t = dfs(dfs, v), T = t;
            if (siz[t] > siz[s]) {
                swap(t, s);
            }
            auto dfs2 = [&](auto&& dfs2, int u) -> void {
                push(u);
                if (ls[u]) dfs2(dfs2, ls[u]);
                if (rs[u]) dfs2(dfs2, rs[u]);
                i64 x = max(val[u], w);
                int t1, t2;
                split(s, x, t1, t2);
                (ans += (sum[t2] - siz[t2] + Mod) % Mod) %= Mod;
                (ans += ((x - 1) * siz[t1]) % Mod) %= Mod;
                s = merge(t1, t2);
            };
            dfs2(dfs2, t);
            auto dfs3 = [&](auto&& dfs3, int u) -> void {
                push(u);
                if (ls[u]) dfs3(dfs3, ls[u]);
                if (rs[u]) dfs3(dfs3, rs[u]);
                i64 x = val[u];
                int t1, t2;
                split(s, x, t1, t2);
                // 重复利用 u 点
                val[u] = sum[u] = x;
                siz[u] = 1;
                ls[u] = rs[u] = 0;
                phi[u] = rng();
                s = merge(t1, merge(u, t2));
            };

            int t1, t2;
            split(T, w, t1, t2);
            tag[t1] = w;
            val[t1] = w;
            sum[t1] = w * siz[t1] % Mod;
            T = merge(t1, t2);

            dfs3(dfs3, t);
        }
        return s;
    };
    dfs(dfs, 1);

    for (int i = 1; i <= __lg(n); ++i) {
        for (int u = 1; u <= n; ++u) {
            fa[u][i][0] = fa[fa[u][i - 1][0]][i - 1][0];
            fa[u][i][1] = max(fa[fa[u][i - 1][0]][i - 1][1], fa[u][i - 1][1]);
        }
    }
    
    auto lca = [&](int u, int v) -> i64 {
        i64 Max = 0;
        if (dep[u] < dep[v]) swap(u, v);
        while (dep[u] != dep[v]) {
            Max = max(Max, fa[u][__lg(dep[u] - dep[v])][1]);
            u = fa[u][__lg(dep[u] - dep[v])][0];
        }
        if (u == v) return Max;
        for (int i = __lg(n); i >= 0; --i) {
            if (fa[u][i][0] == fa[v][i][0]) continue;
            Max = max({ Max, fa[u][i][1], fa[v][i][1] });
            u = fa[u][i][0], v = fa[v][i][0];
        }
        return max({ Max, fa[u][0][1], fa[v][0][1] });
    };

    for (int i = 1; i <= m; ++i) {
        auto& [w, u, v] = E[i];
        ans = ((ans - lca(u, v) + 1) % Mod + Mod) % Mod;
    }

    cout << ans << "\n";
}

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    memset(tag, -1, sizeof(tag));
    
    int T = 1;
    cin >> T;

    while (T--) {
        Thephix();
    }

    return 0;
}