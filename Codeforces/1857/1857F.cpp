#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

template<std::unsigned_integral T>
T floor_sqrt (T n) {
    T t = sqrt(n);
    while (t * t > n) --t;
    while ((t + 1) * (t + 1) < n) ++t;
    return t;
}

void Thephix() {
    int n;
    cin >> n;
    map<int, i64> cnt;
    for (int i = 1; i <= n; ++i) {
        int x; cin >> x;
        cnt[x]++;
    }

    int q;
    cin >> q;
    while (q--) {
        i64 x, y, ans;
        cin >> x >> y;
        i64 delta = x * x - 4 * y;
        if (delta < 0) {
            ans = 0;
        } else if (delta == 0) {
            if (x % 2 == 0) {
                x /= 2;
                ans = cnt[x] * (cnt[x] - 1) / 2;
            } else {
                ans = 0;
            }
        } else  {
            i64 t = floor_sqrt<u64>(delta);
            if (t * t == delta) {
                tie(x, y) = pair { x + t, x - t };
                if (x % 2 == 0 && y % 2 == 0) {
                    ans = cnt[x / 2] * cnt[y / 2];
                } else {
                    ans = 0;
                }
            } else {
                ans = 0;
            }
        }
        cout << ans << " \n"[!q];
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