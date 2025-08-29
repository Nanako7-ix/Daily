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
 * Created: 2025/07/15 10:41:15
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
    int n;
    cin >> n;
    i128 sum = 0;
    vector<pair<char, int>> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].first >> a[i].second;
        sum += a[i].second;
    }

    if (sum > 100) {
        cout << "Too Long\n";
        return;
    }

    for (int i = 1; i <= n; ++i) {
        cout << string(a[i].second, a[i].first);
    }
    cout << "\n";
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