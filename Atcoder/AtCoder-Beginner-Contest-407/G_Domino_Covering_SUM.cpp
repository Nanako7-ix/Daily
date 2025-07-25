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
 * Created: 2025/05/26 00:49:08
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
using f64 = double;

constexpr int inf = 0x3f3f3f3f;
constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;

template<typename Flow, typename Cost, template<typename T> typename Cmp_Fn>
struct CostFlow {
    struct _Edge {
        int to;
        Flow cap;
        Cost cost;
        _Edge(int to, Flow cap, Cost cost) : to(to), cap(cap), cost(cost) {}
    };

    int n;
    vector<_Edge> e;
    vector<vector<int>> g;
    vector<Cost> h, dp;
    vector<int> pre;

    CostFlow(int n) : n(n), g(n + 1), h(n + 1) { }

    void add(int u, int v, Flow cap, Cost cost) {
        g[u].push_back(e.size());
        e.emplace_back(v, cap, cost);
        g[v].push_back(e.size());
        e.emplace_back(u, 0, -cost);
    }

    bool dijkstra (int s, int t) {
        dp.assign(n + 1, numeric_limits<Cost>::max());
        pre.assign(n + 1, -1);
        std::priority_queue<pair<Cost, int>, vector<pair<Cost, int>>, Cmp_Fn<pair<Cost, int>>> q;
        dp[s] = 0;
        q.emplace(dp[s], s);
        while(!q.empty()) {
            auto [d, u] = q.top();
            q.pop();
            if(dp[u] != d) continue;
            for(auto i : g[u]) {
                auto [v, cap, cost] = e[i];
                if(cap > 0 && dp[u] + h[u] - h[v] + cost < dp[v]) {
                    dp[v] = dp[u] + h[u] - h[v] + cost;
                    pre[v] = i;
                    q.emplace(dp[v], v);
                }
            }
        }
        return dp[t] != numeric_limits<Cost>::max();
    }

    pair<Flow, Cost> flow(int s, int t) {
        Flow flow = 0;
        Cost cost = 0;

        for (int i = 0; i < 2; i++) {  
            for (auto e : edges()) {
                h[e.to] = std::min(h[e.to], h[e.from] + e.cost);
            }
        }

        while (dijkstra (s, t)) {
            for(int i = 1; i <= n; ++i) {
                h[i] += dp[i];
            }
            // if (h[t] >= 0) break; 费用优先
            Flow aug = numeric_limits<Flow>::max();
            for(int u = t; u != s; u = e[pre[u] ^ 1].to) {
                aug = min(aug, e[pre[u]].cap);
            }
            for(int u = t; u != s; u = e[pre[u] ^ 1].to) {
                e[pre[u]].cap -= aug;
                e[pre[u] ^ 1].cap += aug;
            }
            flow += aug;
            cost += aug * h[t];
        }
        return {flow, cost};
    }

    struct Edge {
        int from, to;
        Flow cap, flow;
        Cost cost;
    };

    vector<Edge> edges() {
        vector<Edge> res;
        for(int i = 0; i < (int)e.size(); i += 2) {
            Edge x;
            x.from = e[i + 1].to;
            x.to = e[i].to;
            x.cap = e[i].cap + e[i + 1].cap;
            x.flow = e[i].cap;
            x.cost = e[i].cost;
            res.push_back(x);
        }
        return res;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;

    i64 sum = 0;
    vector a(n + 1, vector<i64> (m + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> a[i][j];
            sum += a[i][j];
        }
    }

    int S = n * m + 1, T = S + 1;
    CostFlow<int, i64, greater> mcmf(n * m + 2);
    auto f = [&](int i, int j) { return (i - 1) * m + j; };

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if ((i + j) % 2 == 0) {
                mcmf.add(S, f(i, j), 1, 0);
                if (i + 1 <= n) mcmf.add(f(i, j), f(i + 1, j), 1, a[i][j] + a[i + 1][j]);
                if (i - 1 >= 1) mcmf.add(f(i, j), f(i - 1, j), 1, a[i][j] + a[i - 1][j]);
                if (j + 1 <= m) mcmf.add(f(i, j), f(i, j + 1), 1, a[i][j] + a[i][j + 1]);
                if (j - 1 >= 1) mcmf.add(f(i, j), f(i, j - 1), 1, a[i][j] + a[i][j - 1]);
            } else {
                mcmf.add(f(i, j), T, 1, 0);
            }
        }
    }
    cout << sum - mcmf.flow(S, T).second << endl;
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