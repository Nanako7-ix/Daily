// Author: Nanako7_ix
// Created: 2025/03/31 23:14:34
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
    i64 n, m, HP, k;
    cin >> n >> m >> HP >> k;

    auto f = [&](int x) -> i64 {
        i64 ans = x * n;
        i64 hp = HP;
        for(int i = k; i < x; i += k) {
            hp -= i;
            ans += m;
        }
        ans += (hp + x - 1) / x * m;
        // cout << x << ' ' << ans << endl;
        return ans;
    };

    i64 l = 1, r = HP, ans = INF;
    for(int i = l; i <= r; ++i) {
        cout << f(i) << " \n"[i == r];
    }
    while(l <= r) {
        ans = min(ans, f(l));
        ans = min(ans, f(r));
        i64 m1 = (l + l + r) / 3;
        i64 m2 = (l + r + r) / 3;
        if(m1 > m2) {
            l = m1 + 1;
        } else {
            r = m2 - 1;
        }
    }
    cout << ans << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}