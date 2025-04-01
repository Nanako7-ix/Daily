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
    int n, x, y;
    cin >> n >> x >> y;
    vector<array<int, 3>> a(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i][0] >> a[i][1];
        a[i][2] = i;
    }
    sort(a.begin() + 1, a.end());
    
    vector<array<int, 2>> dp(n + 1);
    for(int i = 1; i <= n; ++i) {
        auto [w, h, id] = a[i];
        if(w <= x || h <= y) {
            dp[id][0] = 0;
        } else {
            dp[id][0] = 1;
        }
    }

    for(int i = 1; i <= n; ++i) {
        auto [xi, yi, ti] = a[i];
        for(int j = 1; j <= i; ++j) {
            auto [xj, yj, tj] = a[j];
            if(xj < xi && yj < yi && dp[tj][0]) {
                if(dp[tj][0] + 1 > dp[ti][0]) {
                    dp[ti][0] = dp[tj][0] + 1;
                    dp[ti][1] = tj;
                }
            }
        }
    }
    int ans = 0, p;
    for(int i = 1; i <= n; ++i) {
        if(dp[i][0] > ans) {
            ans = dp[i][0], p = i;
        }
    }

    if(ans == 0) {
        cout << 0 << endl;
    } else {
        cout << ans << endl;
        vector<int> res;
        for(; p; p = dp[p][1]) {
            res.push_back(p);
        }
        for(auto x : res | views::reverse) {
            cout << x << ' ';
        }
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}