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
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> dep(n + 1);
    vector fa(n + 1, vector (19, array<int, 2> {}));
    fa[1][0][1] = a[1], dep[1] = 1;
    [&](this auto &&dfs, int u) -> void {
        for(auto v : adj[u]) {
            if(v == fa[u][0][0]) continue;
            fa[v][0] = {u, a[u] | a[v]};
            dep[v] = dep[u] + 1;
            dfs(v);
        }
    } (1);
    for(int k = 1; k < 19; ++k) {
        for(int u = 1; u <= n; ++u) {
            auto [v, w] = fa[u][k - 1];
            fa[u][k] = {fa[v][k - 1][0], w | fa[v][k - 1][1]};
        }
    }
    
    vector<vector<int>> nxt(n + 1);
    for(int i = 1; i <= n; ++i) {
        int u = i, now = a[i];
        while((now | fa[i][18][1]) != now) {
            for(int j = 18; j >= 0; --j) {
                if((now | fa[u][j][1]) == now) {
                    u = fa[u][j][0];
                }
            }
            now |= fa[u][0][1];
            u = fa[u][0][0];
            nxt[i].push_back(u);
        }
    }
    
    auto lca = [&](int u, int v) {
        if(dep[u] > dep[v]) swap(u, v);
        while(dep[u] != dep[v]) {
            v = fa[v][__lg(dep[v] - dep[u])][0];
        }
        if(u == v) return u;
        for(int i = 18; i >= 0; --i) {
            if(fa[u][i][0] != fa[v][i][0]) {
                u = fa[u][i][0];
                v = fa[v][i][0];
            }
        }
        return fa[u][0][0];
    };
    
    auto calc = [&](int u, int w) {
        if(u == w) return a[u];
        int ans = 0;
        for(int i = 18; i >= 0; --i) {
            int v = fa[u][i][0];
            if(dep[v] >= dep[w]) {
                ans |= fa[u][i][1];
                u = v;
            }
        }
        return ans;
    };

    int q; cin >> q;
    while(q--) {
        int u, v;
        cin >> u >> v;
        int w = lca(u, v);
        int v_w = calc(v, w), u_w = calc(u, w);
        int ans = max(__builtin_popcount(a[u]), __builtin_popcount(a[v]))+ __builtin_popcount(u_w | v_w);
        for(int i : nxt[u]) {
            if(dep[i] < dep[w]) break;
            ans = max(ans, __builtin_popcount(calc(u, i))
                         + __builtin_popcount(calc(i, w) | v_w));
        }
        for(int i : nxt[v]) {
            if(dep[i] < dep[w]) break;
            ans = max(ans, __builtin_popcount(calc(v, i))
                         + __builtin_popcount(calc(i, w) | u_w));
        }
        cout << ans << " \n"[!q];
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}