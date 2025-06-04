/**
 *
 *  $$$$$$\  $$$$$$\  $$$$$$\  $$\       $$\       $$$$$$\  
 * $$  __$$\ \_$$  _|$$  __$$\ $$ |      $$ |     $$  __$$\ 
 * $$ /  \__|  $$ |  $$ /  $$ |$$ |      $$ |     $$ /  $$ |
 * $$ |        $$ |  $$$$$$$$ |$$ |      $$ |     $$ |  $$ |
 * $$ |        $$ |  $$  __$$ |$$ |      $$ |     $$ |  $$ |
 * $$ |  $$\   $$ |  $$ |  $$ |$$ |      $$ |     $$ |  $$ |
 *  $$$$$$ | $$$$$$\ $$ |  $$ |$$$$$$$$\ $$$$$$$$\ $$$$$$  |
 * \______/  \______|\__|  \__|\________|\________|\______/ 
 *
 * Author:  Nanako7_ix
 * Created: 2025/05/17 20:17:17
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


void solve() {
    i64 n, k;
    cin >> n >> k;
    bitset<60> num(n);
    
    vector dp (60, vector (2, vector<array<i64, 2>> (61)));
    vector vis(60, vector (2, vector<int> (61)));
    auto dfs = [&](auto &&dfs, int p, bool lim, int need, i64 sum) -> array<i64, 2> {
        if (need < 0) return {0LL, 0LL};
        if (p == -1) {
            if (need != 0) {
                array<i64, 2> {0LL, 0LL};
            } return array<i64, 2> {sum % 998244353, 1LL};
        }

        if (vis[p][lim][need]) {
            return dp[p][lim][need];
        }

        dp[p][lim][need] = {0, 0};
        int Max = lim ? num[p] : 1;
        for (int i = 0; i <= Max; ++i) {
            auto [x, y] = dfs(dfs, p - 1, lim && i == Max, need - i, sum << 1 | i);
            if (i == 1) x += i128(y) * (1LL << p) % 998244353;
            (dp[p][lim][need][0] += x) %= 998244353;
            (dp[p][lim][need][1] += y) %= 998244353;
        }

        vis[p][lim][need] = 1;
        return dp[p][lim][need];
    };

    cout << dfs(dfs, 59, 1, k, 0)[0] << endl;
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
    
    int T = 1;
    cin >> T;
    
    while (T--) {
        solve();
    }
    
    return 0;
}