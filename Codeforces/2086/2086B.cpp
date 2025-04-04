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

    for(i64 i = 0; i < k; ++i) {
        i64 need = x - suf[1] * i;
        if(need > suf[1]) continue;
        i64 ans = 0;
        for(int j = n; j >= 1; --j) {
            if(suf[j] >= need) break;
            ans++;
        }
        int p = lower_bound(suf.begin() + 1, suf.end(), need, [](i64 ai, i64 x) {
            return !(ai < x);
        }) - suf.begin() - 1;
        int p = upper_bound(suf.begin() + 1, suf.end(), need, [](i64 x, i64 ai) {
            return ai < x;
        }) - suf.begin() - 1;
        int p = partition_point(suf.begin() + 1, suf.end(), [&](i64 ai) {
            return !(ai < x);
        }) - suf.begin() - 1;
        ans = min(n - p, n);
        cout << n * (k - i) - ans << endl;
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