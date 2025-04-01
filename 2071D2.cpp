#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
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

int solve() {
    i64 n, l, r;
    cin >> n >> l >> r;
    vector<i64> _a(n + 1), _f(n + 1), _g(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> _a[i];
        _f[i] = _f[i - 1] ^ _a[i];
        _g[i] = _g[i - 1] + _f[i];
    }

    if(n % 2 == 0) {
        _a.push_back(_f[++n / 2]);
        _f.push_back(_f.back() ^ _a[n]);
        _g.push_back(_g.back() + _f[n]);
    }

    auto f = [&](this auto&& f, i64 p) -> int {
        if(p <= n) return _f[p];

        if(p % 2 == 1) return f(n);
        return f(n) ^ f(p >> 1);
    };

    auto a = [&](i64 p) -> int {
        if(p <= n) return _a[p];

        return f(p >> 1);
    };

    auto g = [&](this auto&& g, i64 p) -> i64 {
        if(p <= n) return _g[p];

        return g(n) + (p - n) * f(n) + g(p >> 1) - g((n + 1) >> 1);
    };

    for(int i = 1; i <= r; ++i) {
        cout << a(i) << " \n"[i == r];
    }
    for(int i = 1; i <= r; ++i) {
        cout << f(i) << " \n"[i == r];
    }
    for(int i = 1; i <= r; ++i) {
        cout << g(i) << " \n"[i == r];
    }

    if(r <= n) {
        i64 ans = 0;
        for(int i = l; i <= r; ++i) {
            ans += a(i);
        }
        return ans;
    } else if(l <= n) {
        i64 ans = 0;
        for(int i = l; i <= n; ++i) {
            ans += a(i);
        }
        cout << ans << endl;
        ans += 2 * (g(r >> 1) - g(((n + 1) >> 1) - 1));
        return ans;
    } else {
        return 2 * (g(r >> 1) - g((l >> 1) >> 1));
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) cout << solve() << endl;
    return 0;
}