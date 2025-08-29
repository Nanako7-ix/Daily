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
    i64 l, r;
    cin >> l >> r;
    auto cnt = [&](int k) -> i64 {
        return r / k - (l - 1) / k;
    };

    i64 ans = r - l + 1;
    ans -= cnt(2);
    ans -= cnt(3);
    ans -= cnt(5);
    ans -= cnt(7);

    ans += cnt(6);
    ans += cnt(10);
    ans += cnt(14);
    ans += cnt(15);
    ans += cnt(21);
    ans += cnt(35);

    ans -= cnt(30);
    ans -= cnt(42);
    ans -= cnt(70);
    ans -= cnt(105);

    ans += cnt(210);

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