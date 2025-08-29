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
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    int sum = accumulate(a.begin(), a.end(), 0);
    if (sum > m) {
        for (int i = 1; i <= n; ++i) {
            cout << a[i] << " \n"[i == n];
        }
        return;
    }

    m -= sum;
    if (m % 2 == 0) {
        cout << "-1\n";
        return;
    }
    while (m >= 0) {
        if (m % 3 == 0) {
            cout << "-1\n";
            return;
        }
        m -= 2;
    }
    sort(a.begin() + 1, a.end(), [](int x, int y) {
        if (x % 2 == y % 2) {
            return x < y;
        } else {
            return x % 2 < y % 2;
        }
    });
    for (int i = 1; i <= n; ++i) {
        cout << a[i] << " \n"[i == n];
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