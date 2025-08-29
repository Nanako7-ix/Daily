#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr int inf = 2E9;

void Thephix() {
    int n, k;
    cin >> n >> k;
    vector<i64> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> b[i];
    }

    auto check = [&](int x) -> bool {
        i64 cnt = 0;
        for (int i = 1; i <= n; ++i) {
            cnt += max(0LL, (a[i] - x + b[i] - 1) / b[i]);
        }
        return cnt <= k;
    };
    
    i64 lo = 0, hi = inf, res = -1;
    while (lo <= hi) {
        int mid = (lo + hi) >> 1;
        if (check(mid)) {
            res = mid, hi = mid - 1;
        } else lo = mid + 1;
    }

    // > res 的全都被计算，= res 的有部分可以被计算
    assert(res != -1);
    i64 ans = 0, cnt = 0;
    for (int i = 1; i <= n; ++i) {
        int x = max(0LL, (a[i] - res + b[i] - 1) / b[i]);
        ans += ((a[i] + a[i] - (x - 1) * b[i]) * x) / 2;
        k -= x, cnt += (a[i] - x * b[i]) == res;
    }
    ans += res * k;
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