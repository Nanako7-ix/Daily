// Author: Nanako7_ix
// Created: 2025/03/23 23:11:14
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
    i64 n, m, k;
    cin >> n >> m >> k;
    
    i64 l = 1, r = n * m, ans = -1;

    auto check = [&](i64 x) -> bool {
        i64 cnt = 0;
        for(int i = 1; i <= n; ++i) {
            cnt += min(x / i, m);
        }
        return cnt >= k;
    };

    while(l <= r) {
        i64 mid = (l + r) >> 1;
        if(check(mid)) {
            ans = mid, r = mid - 1;
        } else l = mid + 1;
    }
    cout << ans << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}