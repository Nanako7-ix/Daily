// Author: Nanako7_ix
// Created: 2025/04/02 17:37:06
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
    i64 x, y, n, k;
    cin >> x >> y >> n >> k;

    i64 ans = INF;
    for (int op1 = 0; op1 <= n; op1 += k) {
        int op2 = op1 / k;
        i64 cost = op1 * x + op2 * y;

        if (n <= k * (1LL * (op2 + 1) * op2) / 2) {
            ans = min(ans, cost);
            break;
        }

        // 上取整---数论分块
        i64 m = n - k * (1LL * (op2 + 1) * op2) / 2;
        for (i64 i = max(1, op1); i < op1 + k; i++) {
            i64 r = min(op1 + k - 1, i >= m ? inf : (m - 1) / ((m - 1) / i));
            ans = min(ans, cost + (i - op1) * x + (m + i - 1) / i * y);
            i = r;
        }
    }

    cout << ans << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while (T--) solve();
    return 0;
}