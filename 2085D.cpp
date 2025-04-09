// Author: Nanako7_ix
// Created: 2025/04/08 00:51:04
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
    int n, k;
    cin >> n >> k;
    vector<i64> a(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    i64 ans = 0, r = k;
    priority_queue<i64, vector<i64>, greater<i64>> q;
    for(int i = n - k; i >= 1; --i) {
        if (r >= k) {
            q.push(a[i]), ans += a[i];
            r -= k;
        } else {
            r++;
            if(!q.empty() && q.top() < a[i]) {
                ans -= q.top(), q.pop();
                q.push(a[i]), ans += a[i];
            }
        }
    }
    cout << ans << endl;
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