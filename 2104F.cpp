/**
 * Author:  Nanako7_ix
 * Created: 2025/04/28 23:54:38
 * 好想和 めぐる 一起打 xcpc 啊
 */
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define setpre(x) fixed << setprecision(x)
#define debug(x) cerr << #x << " = " << x << "\n"
// #define endl "\n"
using namespace std;
using namespace __gnu_pbds;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

constexpr int inf = 0x3f3f3f3f;
constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;
constexpr int Mod = 998244353;

i64 F[10];

i64 f(int x) {
    int y = x + 1;
    i64 ans = 0;
    while (x) {
        (ans += F[x % 10]) %= Mod;
        x /= 10;
    }
    while (y) {
        (ans += F[y % 10]) %= Mod;
        y /= 10;
    }
    return ans;
}

void solve() {
    int N;
    cin >> N;
    F[0] = 114514;
    for (int i = 1; i < 10; ++i) {
        F[i] = F[i - 1] * 114514 % Mod;
    }
    map<i64, int> mp;
    for (int i = 1; i <= N; ++i) {
        if (mp[f(i)]) {
            cout << mp[f(i)] << ' ' << i << endl;
        }
        mp[f(i)] = i;
    }
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