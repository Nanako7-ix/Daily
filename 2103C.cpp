/**
 * Author: Nanako7_ix
 * Created: 2025/04/21 23:37:52
 */
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
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        a[i] = a[i] <= k;
    }

    vector<int> lft, rgt;
    for (int i = 1, cnt = 0; i < n; ++i) {
        cnt += a[i] == 1;
        if (cnt >= (i + 1) / 2) {
            lft.push_back(i);
        }
    }
    for (int i = n, cnt = 0; i > 1; --i) {
        cnt += a[i] == 1;
        if (cnt > (n - i) / 2) {
            rgt.push_back(i);
        }
    }

    if (lft.size() >= 3 || rgt.size() >= 3) {
        cout << "YES\n";
        return;
    }
    if (lft.size() == 2) {
        int l = lft[0] + 1, r = lft[1], cnt = 0;
        for (int i = l; i <= r; ++i) {
            cnt += a[i] == 1;
        }
        if (cnt > (r - l) / 2) {
            cout << "YES\n";
            return;
        }
    }
    if (rgt.size() == 2) {
        int l = rgt[1], r = rgt[0] - 1, cnt = 0;
        for (int i = l; i <= r; ++i) {
            cnt += a[i] == 1;
        }
        if (cnt > (r - l) / 2) {
            cout << "YES\n";
            return;
        }
    }
    if (lft.empty() || rgt.empty()) {
        cout << "NO\n";
        return;
    }
    if (lft[0] < rgt[0]) {
        cout << "YES\n";
        return;
    }
    cout << "NO\n";
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