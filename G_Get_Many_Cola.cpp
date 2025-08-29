#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr int K = 300;
constexpr int N = 100000;

void Thephix() {
    i64 n, m;
    cin >> n >> m;
    array<int, K + 1> a {};
    for (int i = 1; i <= m; ++i) {
        int x, y;
        cin >> x >> y;
        a[x] = max(a[x], y);
    }

    i64 ans = 0;
    array<i64, N + 1> dp {};
    for (int j = 0; j <= N; ++j) {
        for (int x = 1; x <= K; ++x) {
            if (j >= x) {
                dp[j] = max(dp[j], dp[j - x + a[x]] + a[x]);
            }
        }
    }

    for (int x = 1; x <= K; ++x) {
        int cost = x - a[x];
        i64 cnt = n >= N ? ((n - N) / cost + 1) : 0;
        i64 rest = n - cnt * cost;
        ans = max(ans, cnt * a[x] + dp[rest]);
    }

    cout << n + ans << "\n";
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