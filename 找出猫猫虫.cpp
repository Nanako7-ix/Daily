// Author: Nanako7_ix
// Created: 2025/03/29 15:19:49
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
    vector<i64> l(n + 1), r(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> l[i] >> r[i];
        l[i] += l[i - 1];    
        r[i] += r[i - 1];    
    }

    if(l[n] > 0 || r[n] < 0) {
        cout << "No\n";
        return;
    }

    cout << "Yes\n";
    i64 sum = 0;
    for(int i = 1; i <= n; ++i) {
        array<i64, 2> a { l[n] - l[i] + sum, r[n] - r[i] + sum };
        swap(a[0], a[1]);
        a[0] = max(-a[0], l[i] - l[i - 1]);
        a[1] = min(-a[1], r[i] - r[i - 1]);
        cout << a[0] << " \n"[i == n];
        sum += a[0];
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}