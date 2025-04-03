// Author: Nanako7_ix
// Created: 2025/04/03 22:37:32
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
    i64 n, k, x;
    cin >> n >> k >> x;
    vector<i64> a(n + 1), suf(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for(int i = n; i >= 1; --i) {
        suf[i] = a[i] + (i == n ? 0 : suf[i + 1]);
    }
    for(int i = 1; i <= n; ++i) {
        suf[i] *= -1;
    }
    i64 sum = -suf[1];

    for(i64 i = 0; i < k; ++i) {
        i64 now = sum * i;
        i64 need = x - now;
        if(need > sum) continue;
        int p = upper_bound(suf.begin() + 1, suf.end(), -need) - suf.begin() - 1;
        cout << max((k - i - 1) * n + p, 0LL) << endl;
        return;
    }
    cout << "0\n";
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}