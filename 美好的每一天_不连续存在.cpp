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
 * Author:  Thephix
 * Created: 2025/07/16 15:26:53
 * 好想和 めぐる 一起打 xcpc 啊
 */
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr int Tpx = 0;
constexpr int inf = 1E9;
constexpr i64 INF = 4E18;

struct mat {
    i64 a, b, c, d;
    mat (i64 a, i64 b, i64 c, i64 d) {
        this -> a = a;
        this -> b = b;
        this -> c = c;
        this -> d = d;
    }
    mat operator* (const mat& o) {
        return mat {
            (a * o.a + b * o.c) % 1000000007,
            (a * o.b + b * o.d) % 1000000007,
            (c * o.a + d * o.c) % 1000000007,
            (c * o.b + d * o.d) % 1000000007,
        };
    }
};

void Meguru() {
    int n;
    cin >> n;
    mat B {1, 1, 1, 0};
    for (int i = 1; i <= n; ++i) {
        B = B * B;
    }
    cout << B.c << ' ' << B.d << "\n";

}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T = 1;
    // cin >> T;

    while (T--) {
        Meguru();
    }

    return Tpx;
}