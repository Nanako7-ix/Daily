// Author: Nanako7_ix
// Created: 2025/03/27 23:26:41
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

    vector<array<int, 2>> f(n + 1);
    for(int i = 2; i <= n; ++i) {
        f[i][0] = f[i - 1][0];
        if(a[i - 1] <= a[i]) {
            f[i][0]++;
        }
    }

    int res = 0;
    for(int i = 1; i < n; ++i) {
        res += a[i] >= a[i + 1];
    }

    int ans = inf;
    for(int i = 1; i <= n; ++i) {
        ans = min(ans, f[i][0] + res + (i != 1));
        res -= a[i] >= a[i + 1];
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