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
 * Created: 2025/07/15 10:44:40
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

void Meguru() {
    i64 B, n;
    cin >> B >> n;

    auto gen = [](int l, int mid) {
        i64 ans = l;
        if (mid != -1) {
            ans = ans * 10 + mid;
        }
        for (; l; l /= 10) {
            ans = ans * 10 + l % 10;
        }
        return ans;
    };

    auto check = [B](i64 n) {
        vector<int> res;
        while (n) {
            res.push_back(n % B);
            n /= B;
        }
        for (int i = 0, j = res.size() - 1; i < j; ++i, --j) {
            if (res[i] != res[j]) return false;
        }
        return true;
    };

    i64 ans = 0;
    for (int mid = -1; mid < 10; ++mid) {
        for (int i = 0; i < 1E6; ++i) {
            i64 x = gen(i, mid);
            if (x <= n && check(x)) ans += x;
        }
    }
    cout << ans << "\n";
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