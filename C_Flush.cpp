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
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    
    sort(a.begin() + 1, a.end());
    vector<i64> pre(n + 1);
    for (int i = 1; i <= n; ++i) {
        pre[i] = a[i] + pre[i - 1];
    }
    
    i64 sum = accumulate(a.begin() + 1, a.end(), 0LL);
    while (q--) {
        i64 b;
        cin >> b;
        
        auto check = [&](i64 x) -> bool {
            int p = lower_bound(a.begin() + 1, a.end(), b) - a.begin();
            return (n - p + 1) * (b - 1) + pre[p - 1] < x;
        };
        
        i64 l = b, r = sum, res = -1;
        while (l <= r) {
            i64 m = (l + r) >> 1;
            if (check(m)) {
                res = m, r = m - 1;
            } else l = m + 1;
        }
        cout << res << "\n";
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