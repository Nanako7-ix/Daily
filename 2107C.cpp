/**
 * Author:  Nanako7_ix
 * Created: 2025/05/05 22:50:04
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

constexpr int inf = 0x3f3f3f3f;
constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;

void solve() {
    i64 n, k;
    string s;
    cin >> n >> k >> s;
    set<int> p;
    vector<i64> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        if (s[i - 1] == '0') {
            p.insert(i);
            a[i] = -1E18;
        }
    }

    i64 ans = 0, sum = 0;
    for (int i = 1; i <= n; ++i) {
        sum += a[i];
        if (sum < 0) sum = 0;
        ans = max(ans, sum);
    }

    if (ans > k) {
        cout << "NO\n";
    } else if (ans == k) {
        cout << "YES\n";
        for (int i = 1; i <= n; ++i) {
            cout << a[i] << " \n"[i == n];
        }
    } else if (p.empty()) {
        cout << "NO\n";
    } else {
        cout << "YES\n";

        int x = *p.begin();
        int l = x, r = x;
        while (r + 1 <= n && a[r + 1] >= -k) ++r;
        while (l - 1 >= 1 && a[l - 1] >= -k) --l;
        for (i64 i = r, sum = 0; i > x; --i) {
            sum += a[i];
            if (sum <= 0) {
                r = i - 1, sum = 0;
            }
        }
        for (i64 i = l, sum = 0; i < x; ++i) {
            sum += a[i];
            if (sum <= 0) {
                l = i + 1, sum = 0;
            }
        }

        a[x] = 0;
        a[x] = k - accumulate(a.begin() + l, a.begin() + r + 1, 0LL);
        for (int i = 1; i <= n; ++i) {
            cout << a[i] << " \n"[i == n];
        }
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