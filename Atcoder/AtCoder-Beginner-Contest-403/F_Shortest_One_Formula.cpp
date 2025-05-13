/**
 * Author:  Nanako7_ix
 * Created: 2025/04/29 01:03:05
 * 好想和 めぐる 一起打 xcpc 啊
 */
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

template<typename T>
bool chmin(T& x, const T& y) {
    if (y < x) {
        x = y; return true;
    } return false;
}

void solve() {
    int n;
    cin >> n;

    // 直接是数字  最后一步是+  最后一步是*
    vector dp(n + 1, array { array<int, 3> {inf, 0, 0}, array<int, 3> {inf, 0, 0}, array<int, 3> {inf, 0, 0} });

    for (int i = 1, t = 1; i <= n; i = 10 * i + 1, ++t) {
        dp[i][0] = { t, 0, 0 };
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i - j; ++j) {
            if (chmin(
                    dp[i][1][0],
                    min({dp[j][0][0], dp[j][1][0], dp[j][2][0]}) +
                    1 +
                    min({dp[i - j][0][0], dp[i - j][1][0], dp[i - j][2][0]})
            )) {
                dp[i][1][1] = j;
                dp[i][1][2] = 1;
            }
        }
        for (int j = 2; j * j <= i; ++j) {
            if (i % j != 0) continue;
            if (chmin(
                    dp[i][2][0],
                    min({dp[j][0][0], dp[j][1][0] + 2, dp[j][2][0]}) +
                    1 +
                    min({dp[i / j][0][0], dp[i / j][1][0] + 2, dp[i / j][2][0]})
            )) {
                dp[i][2][1] = j;
                dp[i][2][2] = 2;
            }
        }
    }

    vector<array<int, 2>> nxt(n + 1);
    for (int i = 1; i <= n; ++i) {
        int ans = min({dp[i][0][0], dp[i][1][0], dp[i][2][0]});
        if (dp[i][0][0] == ans) {
            nxt[i] = {0, 0};
        }
        if (dp[i][1][0] == ans) {
            nxt[i] = {dp[i][1][1], dp[i][1][2]};
        }
        if (dp[i][2][0] == ans) {
            nxt[i] = {dp[i][2][1], dp[i][2][2]};
        }
    }

    auto dfs = [&](auto &dfs, int x) -> pair<string, int> {
        auto [val, op] = nxt[x];
        if (op == 0) return { to_string(x), 0 };
        if (op == 1) {
            auto [s1, op1] = dfs(dfs, val);
            auto [s2, op2] = dfs(dfs, x - val);
            return {s1 + '+' + s2, 1};
        } else {
            auto [s1, op1] = dfs(dfs, val);
            auto [s2, op2] = dfs(dfs, x / val);
            if (op1 == 1) s1 = '(' + s1 + ')';
            if (op2 == 1) s2 = '(' + s2 + ')';
            return {s1 + '*' + s2, 2};
        }
    };

    cout << dfs(dfs, n).first << endl;
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
    
    int T = 1;
    // cin >> T;
    
    while (T--) {
        solve();
    }
    
    return 0;
}