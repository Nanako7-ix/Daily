/**
 *
 *  $$$$$$\  $$$$$$\  $$$$$$\  $$\       $$\       $$$$$$\  
 * $$  __$$\ \_$$  _|$$  __$$\ $$ |      $$ |     $$  __$$\ 
 * $$ /  \__|  $$ |  $$ /  $$ |$$ |      $$ |     $$ /  $$ |
 * $$ |        $$ |  $$$$$$$$ |$$ |      $$ |     $$ |  $$ |
 * $$ |        $$ |  $$  __$$ |$$ |      $$ |     $$ |  $$ |
 * $$ |  $$\   $$ |  $$ |  $$ |$$ |      $$ |     $$ |  $$ |
 *  $$$$$$ | $$$$$$\ $$ |  $$ |$$$$$$$$\ $$$$$$$$\ $$$$$$  |
 * \______/  \______|\__|  \__|\________|\________|\______/ 
 *
 * Author:  Nanako7_ix
 * Created: 2025/06/07 20:05:41
 * 好想和 めぐる 一起打 xcpc 啊
 */
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define setpre(x) fixed << setprecision(x)
#define debug(x) cerr << #x << " = " << x << "\n"
using namespace std;
using namespace __gnu_pbds;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64 = double;

constexpr int inf = 0x3f3f3f3f;
constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;

int solve() {
    int n;
    cin >> n;
    
    auto query = [&](int u, int v) -> bool {
        cout << "? " << u << ' ' << v << endl;
        int res; cin >> res;
        return res == 1;
    };

    int u = -1, v = -1;
    for (int i = 1; i + 1 <= n; i += 2) {
        if (query(i, i + 1)) {
            u = i, v = i + 1;
            break;
        }
    }
    
    if (u == -1 && v == -1) {
        if (n % 2 == 0) return 1;
        if (query(1, n)) {
            u = n, v = 1;
        } else return 1;
    }

    int x = v % n + 1, y = x % n + 1;
    if (query(u, x)) {
        if (query(u, y)) {
            return 2;
        } else return 1;
    } else if (query(v, x)) {
        if (query(v, y)) {
            return 2;
        } else return 1;
    } else return 1;
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T = 1;
    cin >> T;

    while (T--) {
        int ans = solve();
        cout << "! " << ans << endl;
    }

    return 0;
}