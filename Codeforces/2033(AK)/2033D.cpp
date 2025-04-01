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
    vector<i64> pre(n + 1), dp(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> pre[i];
        pre[i] += pre[i - 1];
    }
    map<i64, int> nxt;
    nxt[0] = 0;
    for(int i = 1; i <= n; ++i) {
        if(nxt.contains(pre[i])) {
            int p = nxt[pre[i]];
            dp[i] = p ? 1 + dp[p] : 1;
        }
        dp[i] = max(dp[i], dp[i - 1]);
        nxt[pre[i]] = i;
    }
    cout << dp[n] << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}