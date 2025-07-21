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
    int n, k;
    cin >> n >> k;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    if(n == k) {
        cout << 0 << endl;
        return;
    }

    auto check = [&](int m) -> bool {
        int cnt = 0;
        auto dfs = [&](auto dfs, int u, int fa) -> int {
            int siz = 1;
            for(auto v : adj[u]) {
                if(v == fa) continue;
                siz += dfs(dfs, v, u);
            }
            if(siz > m) {
                cnt++; return 0;
            }
            return siz;
        };
        dfs(dfs, 1, 0);
        return cnt <= k;
    };

    int l = 0, r = n, res = -1;
    while(l <= r) {
        int m = (l + r) >> 1;
        if(check(m)) {
            res = m, r = m - 1;
        } else l = m + 1;
    }
    cout << res << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}