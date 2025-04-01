// Author: Nanako7_ix
// Created: 2025/03/30 16:45:40
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
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i <= n; ++i) {
        int x; cin >> x;
        if(x != -1) {
            adj[x].push_back(i);
        }
    }
    vector<int> dep(n + 1), vis(n + 1);
    for(int i = 1; i <= n; ++i) {
        if(vis[i]) continue;
        [&](this auto dfs, int u) -> void {
            vis[i] = 1;
            for(auto v : adj[u]) {
                dep[v] = dep[u] + 1;
                dfs(v);
            }
        } (i);
    }
    cout << *max_element(dep.begin() + 1, dep.end()) + 1 << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}