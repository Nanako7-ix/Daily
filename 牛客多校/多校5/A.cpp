#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr i64 inf = 4E18;

void Thephix() {
    i64 n, k, s, t;
    cin >> n >> k >> s >> t;
    i64 K = min(k, n - k);

    // 考虑操作偶数次
    i64 ans1 = [&]() -> i64 {
        // 两次操作可以变化
        if (s % 2 != t % 2) {
            return inf;
        }
        return abs(t - s) / K;
    } ();

    i64 ans2 = [&]() -> i64 {

    } ();

    cout << (min(ans1, ans2) >= inf ? -1 : min(ans1, ans2)) << "\n";
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