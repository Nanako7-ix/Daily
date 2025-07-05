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
 * Created: 2025/06/07 20:59:07
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

unordered_map<u64, u64> F;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
u64 f(u64 x) {
    if (F.contains(x)) return F[x];
    return F[x] = rng();
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> deg(n + 1);
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        deg[u]++, deg[v]++;
    }
    if (m == n - 1) {
        cout << "YES\n";
        return;
    }
    if (m != n) {
        cout << "NO\n";
        return;
    }
    
    vector<u64> dp(n + 1);
    queue<int> q;
    for (int u = 1; u <= n; ++u) {
        if (deg[u] == 1) q.push(u);
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto v : adj[u]) {
            if (deg[v] == 0) continue;
            deg[u]--, deg[v]--;
            dp[v] += f(dp[u]);
            if (deg[v] == 1) {
                q.push(v);
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        deg[i] /= 2;
    }

    vector<int> loop;
    for (int i = 1; i <= n; ++i) {
        if (deg[i] != 0) {
            for (int u = i, nxt = 0; deg[u]; u = nxt) {
                loop.push_back(u), deg[u]--;
                for (auto v : adj[u]) {
                    if (deg[v] == 0) continue;
                    nxt = v;
                    break;
                }
            }
            break;
        }
    }

    if (loop.size() % 2 == 1) {
        for (int i = 1; i < (int) loop.size(); ++i) {
            if (dp[loop[i]] != dp[loop[i - 1]]) {
                cout << "NO\n";
                return;
            }
        }
        cout << "YES\n";
    } else {
        for (int i = 2; i < (int) loop.size(); ++i) {
            if (dp[loop[i]] != dp[loop[i - 2]]) {
                cout << "NO\n";
                return;
            }
        }
        cout << "YES\n";
    }
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