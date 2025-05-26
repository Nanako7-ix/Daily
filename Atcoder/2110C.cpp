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
 * Created: 2025/05/24 22:50:48
 * 好想和 めぐる 一起打 xcpc 啊
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
using f64 = double;

constexpr int inf = 0x3f3f3f3f;
constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;

void solve() {
    int n;
    cin >> n;
    vector<int> d(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> d[i];
    }
    vector<array<int, 2>> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i][0] >> a[i][1];
    }
    vector<array<int, 2>> b(n + 1);
    for (int i = 1; i <= n; ++i) {
        auto [l, r] = b[i - 1];
        if (d[i] == 1) {
            l++, r++;
        } else if (d[i] == -1) {
            r++;
        }
        l = max(l, a[i][0]);
        r = min(r, a[i][1]);
        b[i] = {l, r};
        if (l > r) {
            cout << -1 << endl;
            return;
        }
    }
    int h = b[n][0];
    for (int i = n; i >= 1; --i) {
        auto [l, r] = b[i - 1];
        if (d[i] != -1) {
            h -= d[i];
            continue;
        }
        if (h - 1 >= l) {
            d[i] = 1, h--;
        } else d[i] = 0;
    }

    for (int i = 1; i <= n; ++i) {
        cout << d[i] << " \n"[i == n];
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