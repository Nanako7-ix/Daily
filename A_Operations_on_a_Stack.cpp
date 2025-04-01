#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
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
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    vector<array<i64, 2>> dp(n + 1, array<i64, 2> {0, 0});
    dp[1] = {0, a[1]};
    for(int i = 2; i <= n; ++i) {
        dp[i][i & 1] = max(dp[i - 1][i & 1], dp[i - 1][(i & 1) ^ 1] + a[i]);
        dp[i][i & 1 ^ 1] = dp[i - 1][i & 1 ^ 1];
    }
    cout << dp[n][n & 1] << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}