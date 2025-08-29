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
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; ++i) {
        int Max = *max_element(a.begin() + 1, a.end());
        int Min = *min_element(a.begin() + 1, a.end());
        if (Max - Min <= 1) {
            break;
        }
        int v = (Max + Min) / 2;
        for (int j = 1; j <= n; ++j) {
            a[j] = abs(a[j] - v);
        }
    }

    i64 ans = 0, sum = 0;
    sort(a.begin() + 1, a.end());
    for (int i = 1; i <= n; ++i) {
        (ans += 1LL * (i - 1) * a[i] % Mod) %= Mod;
        (ans += Mod - sum) %= Mod;
        (sum += a[i]) %= Mod;
    }
    cout << ans << '\n';
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