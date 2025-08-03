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
    vector<int> a(n + 1);
    array<array<array<i64, 2>, 2>, 30> cnt {};
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        int tot = 0;
        for (int j = 0; j < 30; ++j) {
            tot ^= a[i] >> j & 1;
            cnt[j][a[i] >> j & 1][tot & 1]++;
        }
    }

    i64 ans = 0;
    for (int i = 1; i <= n; ++i) {
        int tot = 0;
        for (int j = 0; j < 30; ++j) {
            tot ^= a[i] >> j & 1;
            cnt[j][a[i] >> j & 1][tot & 1]--;
            ans += cnt[j][(a[i] >> j & 1) ^ 1][tot ^ 1] << j;
        }
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