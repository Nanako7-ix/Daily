/**
 * Author: Nanako7_ix
 * Created: 2025/04/11 19:59:48
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

constexpr int inf = 0x3f3f3f3f;
constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;

void solve() {
    array<int, 4> c {};
    cin >> c[1] >> c[2] >> c[3];

    int n = accumulate(c.begin(), c.end(), 0);
    vector<int> f(n + 1);
    array<vector<int>, 4> p {};
    for(int i = 1; i <= n; ++i) {
        cin >> f[i];
        p[f[i]].push_back(i);
    }

    // q / p 没有匹配的
    // c 还能用的
    priority_queue<array<int, 2>> q;
    q.push({ (int) p[1].size(), 1 });
    q.push({ (int) p[2].size(), 2 });
    q.push({ (int) p[3].size(), 3 });
    while (q.size()) {
        auto [cx, x] = q.top(); q.pop();
        int y;
        if(x == 1) {
            y = c[2] < c[3] ? 3 : 2;
        }
        if(x == 2) {
            y = c[1] < c[3] ? 3 : 1;
        }
        if(x == 3) {
            y = c[1] < c[2] ? 2 : 1;
        }
        if(c[y] == 0) break;

        f[p[x].back()] = y;
        p[x].pop_back(), c[y]--;
        if(!p[x].empty()) q.push({ (int) p[x].size(), x });
    }
    for(int i = 1; i <= n; ++i) {
        cout << f[i] << " \n"[i == n];
    }
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