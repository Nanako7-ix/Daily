// Author: Nanako7_ix
// Created: 2025/04/09 00:26:12
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
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    
    int lo = 0, hi = n, res = -1;
    auto check = [&](int x) -> bool {
        int f = 0, ok = 0;
        vector<int> cnt(x);
        for (int i = 1; i <= n; ++i) {
            if (a[i] < x && cnt[a[i]] == f) {
                cnt[a[i]]++, ok++;
            }
            if (ok == x) {
                f++, ok = 0;
            }
        }
        return f >= k;
    };
    while(lo <= hi) {
        int mid = (lo + hi) >> 1;
        if(check(mid)) {
            res = mid, lo = mid + 1;
        } else hi = mid - 1;
    }
    cout << res << endl;
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
    
    int T = 1;
    cin >> T;
    
    while (T--) {
        solve();
    }
    
    return 0;
}