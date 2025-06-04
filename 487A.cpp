/**
 * Author: Nanako7_ix
 * Created: 2025/04/16 10:56:53
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
    // hp, atk, def
    array<int, 3> M, Y, C;
    cin >> Y[0] >> Y[1] >> Y[2];
    cin >> M[0] >> M[1] >> M[2];
    cin >> C[0] >> C[1] >> C[2];
    int ans = inf;
    for (int i = 1; i <= M[0]; ++i) {
        int atk = max((M[0] + i - 1) / i + M[2] - Y[1], 0);
        int hp  = max(i * max(M[1] - Y[2], 0) - Y[0] + 1, 0);
        int def = max(M[1] - (Y[0] + i - 1) / i - Y[2] + 1, 0);
        ans = min({ans, atk * C[1] + hp * C[0], atk * C[1] + def * C[2]});
    }
    cout << ans << endl;
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