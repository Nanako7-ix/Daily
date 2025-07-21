// Author: Nanako7_ix
// Created: 2025/03/29 00:01:44
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

constexpr int inf = 2e9;
constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<i64> a(n + 1), b(m + 1), all { -inf, inf };
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
        all.push_back(a[i]);
    }
    for(int i = 1; i <= m; ++i) {
        cin >> b[i];
        all.push_back(b[i]);
    }
    
    sort(a.begin() + 1, a.end());
    sort(b.begin() + 1, b.end());
    sort(all.begin(), all.end());
    
    vector<i64> prea(n + 1), preb(m + 1);
    for(int i = 1; i <= n; ++i) {
        prea[i] = prea[i - 1] + a[i];
    }
    for(int i = 1; i <= m; ++i) {
        preb[i] = preb[i - 1] + b[i];
    }

    array<i64, 2> ans { INF, -inf };
    for(int i = 1; i < (int) all.size(); ++i) {
        int p1 = upper_bound(a.begin() + 1, a.end(), all[i - 1]) - a.begin() - 1;
        int p2 = upper_bound(b.begin() + 1, b.end(), all[i - 1]) - b.begin() - 1;

        auto f = [&](i64 k) -> i64 {
            i64 resa = prea[n] - 2 * prea[p1] - (n - 2 * p1) * k;
            i64 resb = preb[m] - 2 * preb[p2] - (m - 2 * p2) * k;
            return abs(resa - resb);
        };

        i64 l = all[i - 1], r = all[i];
        while(l <= r) {
            ans = min(ans, array<i64, 2> { f(l),l });
            ans = min(ans, array<i64, 2> { f(r),r });
            i64 m1 = (l + l + r) / 3;
            i64 m2 = (l + r + r) / 3;
            if(f(m1) > f(m2)) {
                l = m1 + 1;
            } else {
                r = m2 - 1;
            }
        }
    }
    cout << ans[1] << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}