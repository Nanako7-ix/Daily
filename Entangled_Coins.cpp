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
    i64 n, k, s, t;
    cin >> n >> k >> s >> t;

    int l = s, r = s, cnt = 0;
    while (true) {
        i64 ans = 114514;
        for (int u = l; u <= r; u += 2) {
            if (abs(u - t) % k == 0) {
                ans = min(ans, cnt + abs(u - t) / k);
            }
        }
        if (ans != 114514) {
            cout << ans << "\n";
            return;
        }
        int Min = n, Max = 0;
        for (i64 u = l; u <= r; u += 2) {
            for (int x = max(0LL, u + k - n); x <= min(u, k); ++x) {
                int v = u + k - 2 * x;
                Min = min(Min, v);
                Max = max(Max, v);
            }
        }
        l = Min, r = Max;
        cout << l << ' ' << r << "\n";
        cnt++;
    }
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