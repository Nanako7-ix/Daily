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
    i64 n, m;
    cin >> n >> m;
    vector<array<i64, 2>> a(m + 1);
    for (int i = 1; i <= m; ++i) {
        cin >> a[i][0] >> a[i][1];
        a[i][1] = a[i][0] - a[i][1];
    }
    sort(a.begin() + 1, a.end());

    vector<array<i64, 2>> stk;
    for (int i = 1; i <= m; ++i) {
        auto [need, cost] = a[i];
        if (stk.empty() || cost < stk.back()[1]) {
            stk.push_back(a[i]);
        }
    }

    i64 ans = 0;
    while (!stk.empty()) {
        auto [need, cost] = stk.back();
        stk.pop_back();
        if (n < need) continue;
        i64 cnt = max((n - need) / cost + 1, 0LL);
        ans += cnt;
        n -= cnt * cost;
    }
    cout << ans << "\n";
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