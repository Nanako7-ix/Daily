#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

int log(i64 n) {
    return __lg(n - 1) + 1;
}

constexpr i64 inf = 1E15;

void Thephix() {
    int n;
    cin >> n;
    vector<i64> a(n + 1), pre(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        pre[i] = pre[i - 1] + a[i];
    }

    auto get = [&](int l, int r, int k) {
        i64 L1 = pre[k] - pre[l - 1];
        i64 L2 = pre[r] - pre[k];
        return pair { abs(L1 - L2), min(L1, L2) * log(L1 + L2) };
    };

    vector Min (n + 1, vector<vector<array<i64, 2>>> (n + 1));
    for (int len = 2; len <= n; ++len) {
        for (int l = 1, r = len; r <= n; ++l, ++r) {
            Min[l][r].reserve(r - l);
            for (int k = l; k < r; ++k) {
                auto [lim, val] = get(l, r, k);
                if (l != k) {
                    auto it = ranges::upper_bound(Min[l][k], array {lim, inf});
                    if (it == Min[l][k].begin()) {
                        val += inf;
                    } else {
                        val += (it - 1) -> operator[](1);
                    }
                }
                if (k + 1 != r) {                    
                    auto it = ranges::upper_bound(Min[k + 1][r], array {lim, inf});
                    if (it == Min[k + 1][r].begin()) {
                        val += inf;
                    } else {
                        val += (it - 1) -> operator[](1);
                    }
                }
                Min[l][r].push_back(array { lim, val });
                if (len == n) {
                    cout << (val < inf ? val : -1) << " \n"[k == n - 1];
                }
            }
            ranges::sort(Min[l][r]);
            for (int i = 1; i < (int) Min[l][r].size(); ++i) {
                Min[l][r][i][1] = min(Min[l][r][i][1], Min[l][r][i - 1][1]);
            }
        }
    }
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T = 1;
    cin >> T;

    while (T--) {
        Thephix();
    }

    return 0;
}