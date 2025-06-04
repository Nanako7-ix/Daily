/**
 *
 *  $$$$$$\  $$$$$$\  $$$$$$\  $$\       $$\       $$$$$$\  
 * $$  __$$\ \_$$  _|$$  __$$\ $$ |      $$ |     $$  __$$\ 
 * $$ /  \__|  $$ |  $$ /  $$ |$$ |      $$ |     $$ /  $$ |
 * $$ |        $$ |  $$$$$$$$ |$$ |      $$ |     $$ |  $$ |
 * $$ |        $$ |  $$  __$$ |$$ |      $$ |     $$ |  $$ |
 * $$ |  $$\   $$ |  $$ |  $$ |$$ |      $$ |     $$ |  $$ |
 *  $$$$$$ | $$$$$$\ $$ |  $$ |$$$$$$$$\ $$$$$$$$\ $$$$$$  |
 * \______/  \______|\__|  \__|\________|\________|\______/ 
 *
 * Author:  Nanako7_ix
 * Created: 2025/05/16 21:31:32
 * 好想和 めぐる 一起打 xcpc 啊
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

struct SCC {
    int n;
    vector<vector<int>> adj;
    vector<int> stk;
    vector<int> dfn, low, bel;
    int cur, cnt;
    
    SCC () = default;
    SCC (int n) { init(n); }
    
    void init(int n) {
        this -> n = n;
        adj.assign(n + 1, {});
        dfn.assign(n + 1, 0);
        low.assign(n + 1, 0);
        bel.assign(n + 1, 0);
        stk.clear();
        cur = cnt = 0;
    }
    
    void add(int u, int v) {
        adj[u].push_back(v);
    }
    
    void tarjan(int u) {
        dfn[u] = low[u] = ++cur;
        stk.push_back(u);
        
        for (auto v : adj[u]) {
            if (dfn[v] == 0) {
                tarjan(v);
                low[u] = min(low[u], low[v]);
            } else if (bel[v] == 0) {
                low[u] = min(low[u], dfn[v]);
            }
        }
        
        if (dfn[u] == low[u]) {
            int x = cnt++;
            do {
                bel[x = stk.back()] = cnt;
                stk.pop_back();
            } while (x != u);
        }
    }
    
    vector<int> work() {
        for (int i = 1; i <= n; i++) {
            if (dfn[i] == 0) tarjan(i);
        }
        return bel;
    }
    
    struct Graph {
        int n;
        vector<vector<int>> adj;
    };
    
    Graph getGraph() {
        work();

        Graph g;
        g.n = cnt;
        g.adj.assign(g.n + 1, {});
        for (int u = 1; u <= n; ++u) {
            for (auto v : adj[u]) {
                if (bel[u] != bel[v]) {
                    g.adj[bel[u]].push_back(bel[v]);
                }
            }
        }
        
        return g;
    }
};

class DSU {
private:
    int n, cnt;
    std::vector<int> f, siz;
public:
    DSU() = default;

    DSU(int n) { init(n); }

    void init(int n) {
        this -> n = n;
        cnt = n;
        f.resize(n + 1);
        siz.assign(n + 1, 1);
        std::iota(f.begin(), f.end(), 0);
    }

    int find(int x) {
        if(f[x] == x) return x;
        return f[x] = find(f[x]);
    }

    bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return 0;
        cnt--, siz[x] += siz[y];
        return f[y] = x;
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    int size(int x) {
        return siz[find(x)];
    }

    int count() const {
        return cnt;
    }
};

void solve() {
    int N, M;
    cin >> N >> M;
    SCC scc(N);
    DSU dsu(N);
    for (int i = 1; i <= M; ++i) {
        int u, v;
        cin >> u >> v;
        scc.add(u, v);
        dsu.merge(u, v);
    }

    if (dsu.count() != 1) {
        cout << 0 << endl;
        return;
    }

    auto [n, adj] = scc.getGraph();
    auto bel = scc.work();

    vector<int> a(n + 1);
    for (int i = 1; i <= N; ++i) {
        a[bel[i]]++;
    }

    vector<int> ans;
    for (int i = 1; i <= n; ++i) {
        if (adj[i].empty()) {
            ans.push_back(i);
        }
    }

    if (ans.size() == 1) {
        cout << a[ans[0]] << endl;
    } else {
        cout << 0 << endl;
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