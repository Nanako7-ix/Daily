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
    int n, k;
    cin >> n >> k;
    i64 ans = 0;
    vector<array<i64, 2>> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i][0];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> a[i][1];
        if (a[i][0] > a[i][1]) {
            swap(a[i][0], a[i][1]);
        }
    }
    sort(a.begin() + 1, a.end(), [](array<i64, 2> x, array<i64, 2> y) {
        return x[1] < y[1];
    });
    for (int i = 1; i <= n; ++i) {
        ans += a[i][1] - a[i][0];
    }
    
    i64 Min = a[n][0], res = 4E18;
    for (int i = n - 1; i >= 1; --i) {
        res = min(res, 2 * max(a[i][0], Min) - 2 * a[i][1]);
        Min = min(Min, a[i][0]);
    }

    cout << max(ans, ans + res) << "\n";
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