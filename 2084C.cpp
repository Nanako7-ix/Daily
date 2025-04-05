// Author: Nanako7_ix
// Created: 2025/04/05 22:44:52
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

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; ++i) {
        cin >> b[i];
    }
    
    vector<array<int, 2>> f(n + 1);
    for(int i = 1; i <= n; ++i) {
        f[i][0] = a[i], f[i][1] = b[i];
    }
    sort(f.begin() + 1, f.end());
    
    int cnt = 0;
    for(int i = 1; i <= n; ++i) {
        auto [x, y] = f[i];
        if(x == y) cnt++;
        else if(f[y][1] != x) {
            cout << "-1\n";
            return;
        }
    }
    if(cnt > n % 2) {
        cout << "-1\n";
        return;
    }
    
    vector<array<int, 2>> q;
    vector<int> vis(n + 1), p(n + 1);
    for(int i = 1; i <= n; ++i) {
        p[a[i]] = i;
    }
    for(int i = 1, j = 1; i <= n; ++i) {
        if(vis[i] || f[i][1] == i) continue;
        int x = i, y = f[i][1];
        if(p[x] != j) {
            int aj = a[j];
            q.push_back({j, p[x]});
            swap(p[a[j]], p[x]);
            a[p[aj]] = aj, a[p[x]] = x;
        }
        if(p[y] != n - j + 1) {
            int aj = a[n - j + 1];
            q.push_back({n - j + 1, p[y]});
            swap(p[a[n - j + 1]], p[y]);
            a[p[aj]] = aj, a[p[x]] = x;
        }
        vis[x] = vis[y] = 1;
        ++j;
    }
    cout << q.size() << endl;
    for(auto [i, j] : q) {
        cout << i << ' ' << j << endl;
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