// Author: Nanako7_ix
// Date: 2025/03/23
// Time: 20:47:50
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
    int n; cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.end());
    vector<int> pre(n + 1);
    for(int i = 1; i <= n; ++i) {
        pre[i] = pre[i - 1] + a[i];
    }

    int ans = inf;
    vector<int> dp(pre[n] + 1);
    dp[0] = 1;
    for(int i = 2; i <= n; ++i) {
        for(int j = pre[n]; j >= a[i - 1]; --j) {
            dp[j] |= dp[j - a[i - 1]];
        }
        for(int j = a[i] + 1; j <= pre[n]; ++j) {
            if(dp[j]) ans = min(ans, a[i] + j);
        }
    }
    cout << (ans == inf ? -1 : ans) << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}