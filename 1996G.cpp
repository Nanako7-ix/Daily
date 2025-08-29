#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

mt19937_64 rng(chrono::steady_clock().now().time_since_epoch().count());

void Thephix() {
    int n, m;
    cin >> n >> m;
    vector<i64> f(n + 1);
    for (int i = 1; i <= m; ++i) {
        int u, v;
        i64 w = rng();
        cin >> u >> v;
        f[u] ^= w, f[v] ^= w;
    }

    int ans = 0;
    map<i64, int> cnt;
    for (int i = 1; i <= n; ++i) {
        f[i] ^= f[i - 1];
        ans = max(ans, ++cnt[f[i]]);
    }

    cout << n - ans << "\n";
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