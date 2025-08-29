#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr int N = 500;

void Thephix() {
    int n;
    cin >> n;
    vector<int> p(n + 1), a(n + 1), b(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> p[i] >> a[i] >> b[i];
    }

    vector<int> prea(n + 1), preb(n + 1);
    for (int i = 1; i <= n; ++i) {
        prea[i] = prea[i - 1] + a[i];
        preb[i] = preb[i - 1] + b[i];
    }

    vector<vector<int>> dp(n + 1, vector<int> (N + 1));
    for (int i = 0; i <= N; ++i) {
        if (p[n] < i) {
            dp[n][i] = max(i - b[n], 0);
        } else {
            dp[n][i] = i + a[n];
        }
    }

    for (int i = n - 1; i >= 1; --i) {
        for (int j = 0; j <= N; ++j) {
            if (p[i] >= j) {
                int now = j + a[i];
                if (now <= N) {
                    dp[i][j] = dp[i + 1][now];
                } else {
                    auto it = lower_bound(preb.begin() + 1, preb.end(), now + preb[i] - N);
                    int x = it - preb.begin();
                    if (x >= n) {
                        dp[i][j] = now - preb[n] + preb[i];
                    } else {
                        now -= preb[x] - preb[i];
                        dp[i][j] = dp[x + 1][now];
                    }
                }
            } else {
                dp[i][j] = dp[i + 1][max(j - b[i], 0)];
            }
        }
    }

    int q;
    cin >> q;
    while (q--) {
        int val;
        cin >> val;

        auto it = lower_bound(preb.begin(), preb.end(), val - N);
        int x = it - preb.begin();
        if (x >= n) {
            cout << val - preb[n] << "\n";
        } else {
            cout << dp[x + 1][val - preb[x]] << "\n";
        }
    }
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