#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr i64 Mod = 998244353;

void Thephix() {
    int n, q;
    cin >> n >> q;

    int Max = n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        Max = max(Max, a[i]);
    }

    vector<i64> Hash(Max + 1);
    mt19937_64 rng(chrono::steady_clock().now().time_since_epoch().count());
    for (int i = 1; i <= Max; ++i) {
        Hash[i] = rng() % Mod;
    }

    for (int i = 1; i <= n; ++i) {
        a[i] = Hash[a[i]];
        (a[i] += a[i - 1]) %= Mod;
    }

    for (int i = 1; i <= Max; ++i) {
        Hash[i] = ((Hash[i] * 2) % Mod + Hash[i - 1]) % Mod;
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        if ((a[r] - a[l - 1] + Mod) % Mod == Hash[(r - l + 1) / 2]) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
}

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T = 1;
    // cin >> T;

    while (T--) {
        Thephix();
    }

    return 0;
}