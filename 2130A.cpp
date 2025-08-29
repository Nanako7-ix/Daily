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
    int n, ans = 0;
    cin >> n;
    int cnt0 = 0, cnt1 = 0;
    for (int i = 1; i <= n; ++i) {
        int x; cin >> x;
        if (x > 1) ans += x;
        if (x == 1) cnt1++;
        if (x == 0) cnt0++;
    }

    int f = min(cnt0, cnt1);
    cnt0 -= f, cnt1 -= f;
    ans += 2 * f;
    ans += cnt1 + cnt0;

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