/**
 * Author:  Nanako7_ix
 * Created: 2025/05/09 22:34:14
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

template<int N>
struct DigitDP {
    vector<i64> power;
    vector<pair<int, array<i64, N>>> dp;
    void init(int width) {
        power.assign(width + 1, 1);
        dp.assign(width, {0, {}});
        power[0] = 1;
        for (int i = 1; i <= width; ++i) {
            power[i] = power[i - 1] * N;
        }
    }
    array<i64, N> solve(i64 x) {
        vector<i64> num(1, 0), sum(1, 0);
        for (i64 p = 1; x; p *= N, x /= N) {
            int d = x % N;
            sum.push_back(d * p + sum.back());
            num.push_back(d);
        }

        auto dfs = [&](auto &&dfs, int p, int lim, int f0) -> array<i64, N> {
            if (p == 0) return {};
            if (lim == 0 && f0 == 0 && dp[p].first != 0) {
                return dp[p].second;
            }

            array<i64, N> ans {};
            int Max = lim ? num[p] : N - 1;

            for (int i = 0; i <= Max; ++i) {
                auto res = dfs(dfs, p - 1, lim && i == Max, f0 && i == 0);
                for (int j = 0; j < N; ++j) {
                    ans[j] += res[j];
                }
                if (f0 && i == 0) continue;
                if (lim && i == Max) {
                    ans[i] += sum[p - 1] + 1;
                } else {
                    ans[i] += power[p - 1];
                }
            }

            if (lim == 0 && f0 == 0) {
                dp[p] = {1, ans};
            }

            return ans;
        };

        return dfs(dfs, num.size() - 1, 1, 1);
    }
};

void solve() {
    DigitDP<10> dp;
    dp.init(12);
    i64 l, r;
    cin >> l >> r;
    auto R = dp.solve(r);
    auto L = dp.solve(l - 1);
    for (int i = 0; i < 10; ++i) {
        cout << R[i] - L[i] << " \n"[i == 9];
    }
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