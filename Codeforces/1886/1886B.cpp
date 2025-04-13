/**
 * Author: Nanako7_ix
 * Created: 2025/04/13 21:28:20
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
    array<int, 2> a, b, p, o{};
    cin >> p[0] >> p[1];
    cin >> a[0] >> a[1];
    cin >> b[0] >> b[1];

    auto d = [](array<int, 2> x, array<int, 2> y) {
        return hypot(x[0] - y[0], x[1] - y[1]);
    };
    
    double l = 0, r = max({d(a, o), d(b, o), d(a, p), d(b, p)});
    
    auto check = [&](double x) {
        if (d(o, a) <= x && d(a, p) <= x) return true;
        if (d(o, b) <= x && d(b, p) <= x) return true;
        if (d(o, a) <= x && d(a, b) <= 2 * x && d(b, p) <= x) return true;
        if (d(o, b) <= x && d(b, a) <= 2 * x && d(a, p) <= x) return true;
        return false;
    };

    for (int i = 1; i <= 100; ++i) {
        double m = (l + r) / 2;
        if (check(m)){
            r = m;
        } else l = m;
    }

    cout << setpre(12) << l << endl;
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