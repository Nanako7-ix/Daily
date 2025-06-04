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
 * Created: 2025/06/04 21:59:54
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

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> deg(n + 1);
    vector<vector<array<int, 2>>> adj(n + 1);
    for (int i = 1; i <= m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        if (u != v) adj[v].push_back({u, w});
        deg[u]++, deg[v]++;    
    }

    vector<int> vis(n + 1);
    multiset<array<int, 2>> del;
    auto dfs = [&](this auto&& dfs, int u) -> void {
        vis[u] = 1;
        for (auto [v, w] : adj[u]) {
            if (vis[v] || w == 1) continue;
            dfs(v);
            if (deg[v] % 2 == 1) {
                del.insert({min(u, v), max(u, v)});
                deg[v]--, deg[u]--;
            }
        }
    };

    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) {
            dfs(i);
            if (deg[i] % 2 == 1) {
                cout << "NO\n";
                return;
            }
        }
    }

    cout << "YES\n";
    m = 0;
    vector<vector<array<int, 2>>> nadj(n + 1);
    for (int u = 1; u <= n; ++u) {
        for (auto [v, w] : adj[u]) {
            if (u > v) continue;
            auto it = del.find({u, v});
            if (w == 0 && it != del.end()) {
                del.erase(it);
            } else {
                m++;
                nadj[u].push_back({v, m});
                nadj[v].push_back({u, m});
            }
        }
    }

    // 返回为 0 为欧拉回路，> 0 为欧拉路径，< 0 为不存在， op 为 0 表示无向，为 1 表示有向
    auto [euler_type, euler_path] = [&](int n, int m, int op, vector<vector<array<int, 2>>> adj) {
        vector<int> vis(m + 1), res;    // 有向时不需要 vis, 无向不需要 deg
        int flag = 0;   // 若flag 最后为 0 ，则为欧拉回路
        for (int i = 1; i <= n; i++) {  // adj 最后一维记录的为边的编号
            if (!op && (adj[i].size() & 1)) {
                if (++flag > 2) return pair{(int)-1, res};
            } if (op && adj[i].size() != deg[i]) {
                switch ((int)adj[i].size() - deg[i]) {
                    case 1 : flag += 1; break;
                    case -1 : flag += 3; break;
                    default : return pair{(int)-1, res};
                }
                if (!(flag & 1) && flag != 4) return pair{(int)-1, res};
            }
            // sort(adj[i].begin(), adj[i].end(), greater());  // 按字典序从小到大
        }
        for (int i = 1; i <= n; i++) {
            auto dfs = [&](auto & dfs, int u) -> void {
                while (adj[u].size()) {
                    auto [v, i] = adj[u].back();
                    adj[u].pop_back();
                    if (vis[i]) continue;   // 有向时不需要
                    vis[i] = 1;
                    dfs(dfs, v);
                }
                res.push_back(u);   // 回溯 push ，为了保证其他环都跑完
            };
            if (!flag && adj[i].size()) { dfs(dfs, i); break; }
            if (!op && (adj[i].size() & 1)) { dfs(dfs, i); break; }
            if (op && adj[i].size() > deg[i]) { dfs(dfs, i); break; }
        }
        if (accumulate(adj.begin() + 1, adj.end(), 0, [&](auto now, auto & x) { return now + x.size(); })) {
            return pair{(int)-1, res};  // 边不联通
        }
        return pair{flag, vector(res.rbegin(), res.rend())};    // reverse 因为是回溯的时候 push
    } (n, m, 0, nadj);

    assert(euler_type == 0);
    cout << euler_path.size() - 1 << "\n";
    for (auto x : euler_path) {
        cout << x << ' ';
    } cout << "\n";
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T = 1;
    cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}