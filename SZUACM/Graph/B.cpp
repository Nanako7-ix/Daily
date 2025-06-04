/**
 * Author:  Thephix
 * Created: 2025/06/04 17:27:49
 */
#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using i128 = __int128;
using u128 = unsigned __int128;
using f64 = double;
using f128 = __float128;
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), pre(n + 1), lft(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        pre[i] = max(pre[i - 1], a[i]);
        int l = 0, r = i - 1;
        while (l <= r) {
            int m = (l + r) >> 1;
            if (pre[m] < a[i]) {
                lft[i] = m + 1, l = m + 1;
            } else r = m - 1;
        }
    }

    int ans = 0;
    for (int i = n, lst = n + 1; i >= 1; --i) {
        if (i < lst) ans++;
        lst = min(lst, lft[i]);
    }
    cout << ans << "\n";
}

signed main() {
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int T = 1;
    std::cin >> T;

    while (T--) {
        solve ();
    }

    return 0;
}