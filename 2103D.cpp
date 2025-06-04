/**
 * Author: Nanako7_ix
 * Created: 2025/04/22 00:10:04
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
    int n;
    cin >> n;
    vector<int> a(n + 1), p(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    int l = 1, L = 1, r = n, R = n, k = *max_element(a.begin() + 1, a.end());
    for (int j = 1; j <= k; ++j) {
        if (j & 1) {
            for (; L <= n && a[L] != -1 && a[L] <= j; ++L) {
                if (a[L] == j) p[L] = r--;
            }
            for (; R >= 1 && a[R] != -1 && a[R] <= j; --R) {
                if (a[R] == j) p[R] = r--;
            }
            for (int i = L; i <= R; ++i) {
                if (a[i] == j) {
                    p[i] = r--;
                }
            }
        } else {
            for (; L <= n && a[L] != -1 && a[L] <= j; ++L) {
                if (a[L] == j) p[L] = l++;
            }
            for (; R >= 1 && a[R] != -1 && a[R] <= j; --R) {
                if (a[R] == j) p[R] = l++;
            }
            for (int i = L; i <= R; ++i) {
                if (a[i] == j) {
                    p[i] = l++;
                }
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (p[i] == 0) p[i] = l;
        cout << p[i] << " \n"[i == n];
    }
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