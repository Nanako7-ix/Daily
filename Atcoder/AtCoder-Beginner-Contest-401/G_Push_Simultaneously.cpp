/**
 * Author: Nanako7_ix
 * Created: 2025/04/13 16:32:08
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
using f128 = __float128;

constexpr int inf = 0x3f3f3f3f;
constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;

template<class Flow>
struct MaxFlow {
    struct _Edge {
        int to;
        Flow cap;
        _Edge(int to, Flow cap) : to(to), cap(cap) {}
    };

    int n, s, t, worked = 0;
    Flow maxflow;
    vector<_Edge> e;
    vector<vector<int>> g;
    vector<int> cur, h;

    MaxFlow(int n, int s, int t) : n(n), s(s), t(t) {
        g.assign(n, {});
        cur.resize(n);
        h.resize(n);
    }

    void add(int u, int v, Flow cap) {
        assert(u > 0 && v > 0);
        u--, v--;
        g[u].push_back(e.size());
        e.emplace_back(v, cap);
        g[v].push_back(e.size());
        e.emplace_back(u, 0);
    }

    bool bfs() {
        h.assign(n, 0);
        queue<int> q;
        h[s] = 1, q.push(s);
        while(!q.empty()) {
            const int u = q.front();
            q.pop();
            for(int i : g[u]) {
                auto [v, cap] = e[i];
                if(cap > 0 && !h[v]) {
                    h[v] = h[u] + 1;
                    if(v == t) return true;
                    q.push(v);
                }
            }
        }
        return false;
    }

    Flow dfs(int u, Flow flow) {
        if(u == t) return flow;
        Flow rest = flow;
        for(int& i = cur[u]; i < (int)g[u].size(); ++i) {
            const int j = g[u][i];
            auto [v, cap] = e[j];
            if(cap > 0 && h[v] == h[u] + 1) {
                Flow cost = dfs(v, min(rest, cap));
                e[j].cap -= cost;
                e[j ^ 1].cap += cost;
                rest -= cost;
                if(rest == 0) return flow;
            }
        }
        return flow - rest;
    }

    Flow operator()() {
        if(worked) return maxflow;
        Flow ans = 0;
        while(bfs()) {
            cur.assign(n, 0);
            ans += dfs(s, numeric_limits<Flow>::max());
        }
        worked = 1;
        return maxflow = ans;
    }

    // cut[i] = 1 -> lft side
    // cut[i] = 0 -> rgt side
    vector<bool> minCut() {
        (*this)();
        vector<bool> cut(n + 1);
        for(int i = 1; i <= n; ++i) {
            cut[i] = h[i - 1] != 0;
        }
        return cut;
    }

    struct Edge {
        int from, to;
        Flow cap, flow;
    };

    vector<Edge> edges() {
        (*this)();
        vector<Edge> res;
        for(int i = 0; i < (int)e.size(); i += 2) {
            Edge x;
            x.from = e[i + 1].to;
            x.to = e[i].to;
            x.cap = e[i].cap + e[i + 1].cap;
            x.flow = e[i + 1].cap;
            res.push_back(x);
        }
        return res;
    }
};

void solve() {
    int n;
    cin >> n;
    vector<array<i64, 2>> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i][0] >> a[i][1];
    }
    for(int i = 1; i <= n; ++i) {
        cin >> b[i][0] >> b[i][1];
    }
    
    vector<vector<i128>> d(n + 1, vector<i128> (n + 1));
    vector<i128> ans(n * n + 1);
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            i128 x = a[i][0] - b[j][0];
            i128 y = a[i][1] - b[j][1];
            d[i][j] = x * x + y * y;
            ans[(i - 1) * n + j] = d[i][j];
        }
    }

    sort(ans.begin() + 1, ans.end());
    auto check = [&](int m) -> bool {
        MaxFlow<int> maxflow(2 * n + 2, 0, n << 1 | 1);
        int S = 1, T = 2 * n + 2;
        for(int i = 1; i <= n; ++i) {
            maxflow.add(S, i + 1, 1);
            maxflow.add(i + n + 1, T, 1);
        }
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) {
                if(d[i][j] <= ans[m]) {
                    maxflow.add(i + 1, j + n + 1, 1);
                }
            }
        }
        return maxflow() == n;
    };

    int lo = 1, hi = n * n, res = -1;
    while (lo <= hi) {
        int m = (lo + hi) >> 1;
        if (check(m)) {
            res = m, hi = m - 1;
        } else lo = m + 1;
    }

    long double l = 0, r = 4E18;
    for(int i = 1; i <= 100; ++i) {
        long double m = (l + r) / 2;
        if (m * m < ans[res]) {
            l = m;
        } else r = m;
    }
    cout << setpre(12) << l << endl;
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