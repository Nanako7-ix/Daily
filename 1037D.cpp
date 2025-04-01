// Author: Nanako7_ix
// Created: 2025/03/30 16:53:11
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

bool solve() {
    int n; cin >> n;

    vector<set<int>> adj(n + 1);
    for(int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].insert(v);
        adj[v].insert(u);
    }

    vector<int> a(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    vector<int> dep(n + 1), fa(n + 1);
    [&](this auto dfs, int u) -> void {
        for(auto v : adj[u]) {
            if(v == fa[u]) continue;
            dep[v] = dep[u] + 1;
            fa[v] = u;
            dfs(v);
        }
    } (1);

    vector<int> b(n + 1);
    for(int i = 1; i <= n; ++i) {
        b[i] = dep[a[i]];
    }

    if(!is_sorted(b.begin() + 1, b.end())) {
        return false;
    }

    vector<int> f { 1 };
    for(int i = 1; i <= *max_element(dep.begin() + 1, dep.end()); ++i) {
        int l = lower_bound(b.begin() + 1, b.end(), i) - b.begin();
        int r = upper_bound(b.begin() + 1, b.end(), i) - b.begin();

        for(int j = l, p = 0; j < r; ++j) {
            if(p == (int) f.size()) return false;
            if(!adj[f[p]].contains(a[j])) p++, j--;
        }

        f = vector (a.begin() + l, a.begin() + r);
    }

    return true;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve() ? cout << "Yes\n" : cout << "No\n";
    return 0;
}