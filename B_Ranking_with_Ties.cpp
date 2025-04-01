// Author: Nanako7_ix
// Created: 2025/03/29 21:46:51
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
    int n, m = 100;
    cin >> n;
    vector<int> a(n + 1);
    vector<vector<int>> p(m + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
        p[a[i]].push_back(i);
    }
    int rank = 1;
    for(int i = m; i >= 1; --i) {
        for(auto x : p[i]) {
            a[x] = rank;
        }
        rank += p[i].size();
    }
    for(int i = 1; i <= n; ++i) {
        cout << a[i] << endl;
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}