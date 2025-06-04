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
#define int i64
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
    auto f = [&](i64 x) -> i64 {
        vector<i64> num(1, 0);
        for (i64 p = 1; x; p *= 10, x /= 10) {
            num.push_back(x % 10);
        }
        int width = num.size() - 1;
        vector<array<bool, 10>> vis(width);
        vector<array<i64, 10>> dp(width);

        auto dfs = [&](auto &&dfs, int p, int lim = 1, int f0 = 1, int bef = 114514) -> i64 {
            if (p == 0) return 1;
            if (lim == 0 && f0 == 0 && vis[p][bef]) {
                return dp[p][bef];
            }
            i64 ans = 0;
            int Max = lim ? num[p] : 10 - 1;
            for (int i = 0; i <= Max; ++i) {
                if (f0 || abs(bef - i) >= 2) {
                    ans += dfs(
                        dfs,
                        p - 1,
                        lim && i == Max,
                        f0 && i == 0,
                        i
                    );
                }
            }
            if (lim == 0 && f0 == 0) {
                vis[p][bef] = 1;
                dp[p][bef] = ans;
            }
            return ans;
        };

        return dfs(dfs, num.size() - 1);
    };

    i64 l, r;
    cin >> l >> r;
    cout << f(r) - f(l - 1) << endl;
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