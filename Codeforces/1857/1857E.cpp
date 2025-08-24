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
    int n;
    cin >> n;
    i64 suml = 0, sumr = 0;
    vector<array<i64, 2>> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i][0];
        a[i][1] = i;
        sumr += a[i][0];
    }
    sort(a.begin() + 1, a.end());

    vector<i64> ans(n + 1);
    for (int i = 1; i <= n; ++i) {
        auto [val, id] = a[i];
        sumr -= val, suml += val;
        ans[id] += sumr - (n - i) * val;
        ans[id] += i * val - suml;
        ans[id] += n;
    }

    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << " \n"[i == n];
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