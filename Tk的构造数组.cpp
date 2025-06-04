/**
 * Author: Nanako7_ix
 * Created: 2025/04/20 19:05:37
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
    int n;
    cin >> n;
    vector<i64> a(n + 1), id(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        a[i] *= i;
    }

    iota(id.begin() + 1, id.end(), 1);
    sort(id.begin() + 1, id.end(), [&](int i, int j) {
        return a[i] > a[j];
    });

    priority_queue<int> q;
    for (int i = 1; i <= n; ++i) {
        int x; cin >> x;
        q.push(x);
    }

    int cnt = 1;
    while (!q.empty()) {
        auto x = q.top();
        q.pop();
        a[id[cnt++]] = x;
    }

    for (int i = 1; i <= n; ++i) {
        cout << a[i] << " \n"[i == n];
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