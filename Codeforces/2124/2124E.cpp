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
 * Created: 2025/07/07 00:03:22
 * 好想和 めぐる 一起打 xcpc 啊
 */
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define debug(x) cerr << "\033[31m" << #x << " = " << x << "\033[0m\n"
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
    vector<i64> a(n + 1), pre(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        pre[i] = pre[i - 1] + a[i];
    }

    if (pre[n] % 2 != 0) {
        cout << "-1\n";
        return;
    }

    i64 half = pre[n] / 2;
    int p = lower_bound(pre.begin() + 1, pre.end(), half) - pre.begin();

    if (pre[p] == half) {
        cout << 1 << "\n";
        for (int i = 1; i <= n; ++i) {
            cout << a[i] << " \n"[i == n];
        }
        return;
    }

    i64 l = half - pre[p - 1];
    i64 r = pre[p] - half;

    vector<i64> first(a);
    first[p] = 0;

    if (pre[n] - pre[p] >= l && pre[p - 1] >= r) {
        vector<i64> second(n + 1);
        first[p] = r, second[p] = l;
        for (int i = p + 1; i <= n; ++i) {
            i64 get = min(l, a[i]);
            first[i] -= get;
            second[i] += get;
            l -= get;
        }

        cout << 2 << "\n";
        for (int i = 1; i <= n; ++i) {
            cout << first[i] << " \n"[i == n];
        }
        for (int i = 1; i <= n; ++i) {
            cout << second[i] << " \n"[i == n];
        }
        return;
    }

    swap(l, r);

    if (pre[n] - pre[p] >= l && pre[p - 1] >= r) {
        vector<i64> second(n + 1);
        first[p] = r, second[p] = l;
        for (int i = p + 1; i <= n; ++i) {
            i64 get = min(l, a[i]);
            first[i] -= get;
            second[i] += get;
            l -= get;
        }

        cout << 2 << "\n";
        for (int i = 1; i <= n; ++i) {
            cout << first[i] << " \n"[i == n];
        }
        for (int i = 1; i <= n; ++i) {
            cout << second[i] << " \n"[i == n];
        }
        return;
    }

    cout << "-1\n";
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