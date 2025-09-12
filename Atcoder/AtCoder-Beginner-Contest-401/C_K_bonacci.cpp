/**
 * Author: Nanako7_ix
 * Created: 2025/04/12 20:16:36
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
constexpr i64 Mod = 1000000000;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<i64> a(n + 1);
    for(int i = 0; i < k && i <= n; ++i) {
        a[i] = i + 1;
    }
    for(int i = k; i <= n; ++i) {
        int l = i - k, r = i - 1;
        a[i] = ((a[r] - (l == 0 ? 0 : a[l - 1])) % Mod + Mod) % Mod;
        a[i] = (a[i - 1] + a[i]) % Mod;
    }
    cout << ((a[n] - a[n - 1]) % Mod + Mod) % Mod << endl;
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
    
    int T = 1;
    // cin >> T;
    
    while (T--) {
        solve();
    }
    
    return 0;
}