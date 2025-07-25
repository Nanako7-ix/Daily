/**
 * Author: Nanako7_ix
 * Created: 2025/04/19 22:35:46
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
    string s;
    cin >> n >> s;
    vector<int> a(n + 1);
    int l = 1, r = n;
    for (int i = n; i > 1; --i) {
        if (s[i - 2] == '>') {
            a[i] = r--;
        } else {
            a[i] = l++;
        }
    }
    a[1] = l;
    for (int i = 1; i <= n; ++i) {
        cout << a[i] << " \n"[i == n];
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