#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

void Thephix() {
    int n, mod;
    cin >> n >> mod;

    i64 ans = 0;
    vector<i64> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        ans += a[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> b[i];
        ans += b[i];
    }

    sort(a.begin() + 1, a.end());
    sort(b.begin() + 1, b.end());

    for (int i = 1; i <= n; ++i) {
        if (a[i] + b.back() >= mod) {
            ans -= mod;
            b.pop_back();
        }
    }

    cout << ans << "\n";
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