#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr i64 inf = 4E18;

void Thephix() {
    int n, m, l;
    cin >> n >> m >> l;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    vector<i64> dp(m, inf);
    dp[0] = 0;
    for (int i = 1; i <= l; ++i) {
        vector<i64> f(m);
        for (int j = i; j <= n; j += l) {
            for (int k = 0; k < m; ++k) {
                f[k] += (k - a[j] + m) % m;
            }
        }
        vector<i64> ndp(m, inf);
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < m; ++k) {
                ndp[(j + k) % m] = min(ndp[(j + k) % m], f[j] + dp[k]);
            }
        }
        swap(ndp, dp);
    }

    cout << dp[0] << "\n";
}

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T = 1;
    // cin >> T;

    while (T--) {
        Thephix();
    }

    return 0;
}