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
    vector<array<int, 3>> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        auto& [l, r, id] = a[i];
        cin >> l >> r;
        id = i;
    }
    sort(a.begin() + 1, a.end(), [](array<int, 3> x, array<int, 3> y) {
        return x[1] - x[0] > y[1] - y[0];
    });

    vector<int> f(2 * n + 1), ans;
    for (int i = 1; i <= n; ++i) {
        int ok = 0;
        auto [l, r, id] = a[i];
        for (int i = l + 1; i <= r; ++i) {
            ok |= f[i] == 0;
        }
        if (ok == 0) continue;
        ans.push_back(id);
        for (int i = l + 1; i <= r; ++i) {
            f[i] = 1;
        }
    }
    cout << ans.size() << "\n";
    for (auto id : ans) {
        cout << id << " ";
    }
    cout << "\n";

    sizeof(long double);
    sizeof(double);
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