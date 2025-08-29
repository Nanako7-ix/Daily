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
    int n, m;
    cin >> n >> m;
    vector a(n + 1, vector<i64> (m + 1));
    for (int i = n; i >= 1; --i) {
        for (int j = m; j >= 1; --j) {
            cin >> a[i][j];
        }
    }
    vector<i64> p(n + m + 1);
    for (int i = n + m; i >= 2; --i) {
        cin >> p[i];
    }

    vector dp(n + 1, vector<i64> (m + 1, inf));
    dp[1][1] = max(p[2] - a[1][1], 0LL);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            dp[i][j] = p[i + j] - a[i][j];
            if (i != 1 || j != 1) {
                dp[i][j] += min(dp[i - 1][j], dp[i][j - 1]);
            }
            dp[i][j] = max(dp[i][j], 0LL);
        }
    }

    cout << dp[n][m] << "\n";
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