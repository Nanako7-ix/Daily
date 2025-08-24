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
    string a, b;
    cin >> n >> a >> b;

    vector<array<i64, 3>> f(n + 1);
    for (int i = 1; i <= n; ++i) {
        f[i] = f[i - 1];
        f[i][b[i - 1] - '0']++;
        f[i][2] += b[i - 1] == '0' ? -1 : 1;
    }
    sort(f.begin() + 1, f.end(), [](array<i64, 3> x, array<i64, 3> y) {
        return x[2] < y[2];
    });
    for (int i = 1; i < n; ++i) {
        f[i + 1][0] += f[i][0];
        f[i + 1][1] += f[i][1];
    }

    i64 ans = 0;
    array<int, 2> cnt {};
    for (int i = 1; i <= n; ++i) {
        cnt[a[i - 1] - '0']++;

        int l = 1, r = n, p = n + 1;
        while (l <= r) {
            int m = (l + r) >> 1;
            if (f[m][2] >= cnt[0] - cnt[1]) {
                p = m, r = m - 1;
            } else l = m + 1;
        }

        ans += f[p - 1][1] + 1LL * (p - 1) * cnt[1];
        ans += f[n][0] - f[p - 1][0] + 1LL * (n - p + 1) * cnt[0];
    }
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