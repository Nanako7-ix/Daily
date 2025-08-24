#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr int N = 30;
constexpr array<i64, 2> f {
    0x15555555,
    0x2AAAAAAA
};

void Thephix() {
    array<i64, 2> g;
    cout << f[0] << endl; cin >> g[0];
    cout << f[1] << endl; cin >> g[1];
    tie(g[0], g[1]) = array {g[1] - 2 * f[1], g[0] - 2 * f[0]};

    cout << "!"  << endl;

    i64 query, ans = 0;
    cin >> query;
    for (int i = 0; i < N; ++i) {
        if (query >> i & 1) {
            ans += 2 << i;
        } else {
            ans += (g[i & 1] >> i & 3) << i;
        }
    }
    cout << ans << endl;
}

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T = 1;
    cin >> T;

    while (T--) {
        Thephix();
    }

    return 0;
}