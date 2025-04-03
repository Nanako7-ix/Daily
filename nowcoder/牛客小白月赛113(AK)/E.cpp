// Author: Nanako7_ix
// Created: 2025/03/28 22:25:52
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
    
    vector<int> lft(n + 1, -inf), rgt(n + 1, inf);
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            if(gcd(a[i], a[j]) == 1) continue;
            if(j < i) lft[i] = max(lft[i], j);
            if(j > i) rgt[i] = min(rgt[i], j);
        }
        if(lft[i] == -inf && rgt[i] == inf) {
            cout << "-1\n";
            return;
        }
    }

    vector<int> dp(n + 1, -inf);
    dp[0] = 0;
    for(int i = 1; i <= n; ++i) {
        int l = i;
        for(int j = i; j >= 1; --j) {
            if(rgt[j] > i) l = min(l, lft[j]);
            if(j <= l) dp[i] = max(dp[i], dp[j - 1] + 1);
        }
    }
    cout << max(dp[n], -1) << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}