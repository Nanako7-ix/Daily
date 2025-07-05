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
 * Created: 2025/06/12 23:23:47
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
    int n;
    i64 k;
    cin >> n >> k;
    vector<i64> p(n + 1), d(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> p[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> d[i];
    }

    map<i64, vector<i64>> add, sub;
    for (int i = 1; i <= n; ++i) {
        add[(p[i] + d[i]) % k].push_back(i);
        sub[((p[i] - d[i]) % k + k) % k].push_back(i);
    }
    
    int m = 2 * n;
    vector<int> deg(m + 1);
    vector<vector<int>> adj(m + 1);
    for (auto [val, a] : add) {
        for (int i = 1; i < (int) a.size(); ++i) {
            adj[a[i - 1]].push_back(a[i] + n);
            deg[a[i] + n]++;
        }
    }
    for (auto [val, a] : sub) {
        for (int i = 1; i < (int) a.size(); ++i) {
            adj[a[i] + n].push_back(a[i - 1]);
            deg[a[i - 1]]++;
        }
    }
    queue<int> q;
    for (int u = 1; u <= m; ++u) {
        if (deg[u] == 0) {
            q.push(u);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto v : adj[u]) {
            deg[v]--;
            if (deg[v] == 0) {
                q.push(v);
            }
        }
    }

    int query; cin >> query;
    while (query--) {
        i64 x;
        cin >> x;
        if (!sub.contains(x % k)) {
            cout << "YES\n";
            continue;
        }
        auto& a = sub[x % k];
        int l = 0, r = a.size() - 1, res = -1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (p[a[mid]] >= x) {
                res = mid, r = mid - 1;
            } else l = mid + 1;
        }
        if (res == -1 || deg[a[res] + n] == 0) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
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