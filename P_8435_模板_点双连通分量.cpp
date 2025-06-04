/**
 * Author: Nanako7_ix
 * Created: 2025/04/13 22:41:32
 */
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
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

struct BlockCutTree {
    int n, cur;
    vector<vector<int>> adj, tr;
    vector<int> dfn, low, stk;

    BlockCutTree (int n = 0) {
        init(n);
    }

    void init(int n) {
        this -> n = n;
        cur = 0;
        adj.assign(n + 1, {});
        tr.assign(n + 1, {});
        dfn.assign(n + 1, 0);
        low.assign(n + 1, 0);
        stk.clear();
    }

    void add(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int u, int fa) {
        int child = 0;
        stk.push_back(u);
        low[u] = dfn[u] = ++cur;
        for (auto v : adj[u]) {
            if (!dfn[v]) {
                child++;
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                if(low[v] >= dfn[u]) {
                    vector<int> vdcc {u};
                    int x;
                    do {
                        x = stk.back();
                        stk.pop_back();
                        vdcc.push_back(x);
                    } while(x != v);

                    for(auto x : vdcc) {
                        tr[x].push_back(tr.size());
                    }

                    tr.push_back(vdcc);
                }
            } else if (v != fa) {
                low[u] = min(low[u], dfn[v]);
            }
        }

        if (fa == 0 && child == 0) {
            tr[u].push_back(tr.size());
            tr.push_back({u});
        }
    }

    void work() {
        for (int i = 1; i <= n; ++i) {
            if (!dfn[i]) dfs(i, 0);
        }
    }

    vector<vector<int>> vdcc() {
        return vector (tr.begin() + n, tr.end());
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    BlockCutTree g(n);
    for(int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        g.add(u, v);
    }
    g.work();
    auto vdcc = g.vdcc();
    cout << vdcc.size() << endl;
    for(auto res : vdcc) {
        cout << res.size() << ' ';
        for(auto x : res) {
            cout << x << ' ';
        }
        cout << endl;
    }
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
    
    int T = 1;
    // cin >> T;
    
    while (T--) {
        solve();
    }
    
    return 0;
}