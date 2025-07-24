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
    vector<i64> h(n + 1), s(n + 1), d(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> h[i] >> s[i] >> d[i];
    }

    i64 ans = 0;
    for (int S = 0; S <= m; ++S) {
        vector<vector<i64>> item(S + 1);
        for (int i = 1; i <= n; ++i) {
            i64 v = h[i] - d[i] * (m - S);
            i64 w = s[i];
            if (w > S) continue;
            item[w].push_back(v);
        }

        vector<i64> dp(S + 1, -inf);
        dp[0] = 0;
        for (int w = 1; w <= S; ++w) {
            int cnt = min<i64> (S / w, item[w].size());
            nth_element(item[w].begin(), item[w].begin() + cnt, item[w].end(), greater<i64> {});
            for (int i = 0; i < cnt; ++i) {
                for (int j = S; j >= w; --j) {
                    dp[j] = max(dp[j], dp[j - w] + item[w][i]);
                }
            }
        }

        ans = max(ans, dp[S]);
    }
    
    cout << ans << "\n";
}

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T = 1;
    cin >> T;

    while (T--) {
        Thephix();
    }

    return 0;
}