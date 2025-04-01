// Author: Nanako7_ix
// Created: 2025/03/25 23:02:07
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
    int n, m, k;
    cin >> n >> m >> k;
    
    int l = 1, r = m, res = -1;
    auto check = [&](int x) -> bool {
        i64 cnt = (m + 1) / (x + 1);
        i64 cost = (cnt - 1) + cnt * x;
        cnt *= x;
        if(cost < m) cnt += m - cost - 1;
        return cnt * n >= k;
    };
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(check(mid)) {
            res = mid, r = mid - 1;
        } else l = mid + 1;
    }
    cout << res << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}