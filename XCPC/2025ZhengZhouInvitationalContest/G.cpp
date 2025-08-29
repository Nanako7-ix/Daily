#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

constexpr i64 inf = 4E18;
constexpr int dir[4][2] = {
    {0, 1}, {1, 0}, {0, -1}, {-1, 0}
};

void solve () {
    int n;
    cin >> n;
    if (n % 3 == 1) {
        if (n == 4) {
            cout << "-1\n";
        } else if (n == 7) {
            cout << "1 2\n";
            cout << "2 3\n";
            cout << "3 4\n";
            cout << "4 5\n";
            cout << "3 6\n";
            cout << "3 7\n";
        } else {
            int k = (n - 1) / 3;
            for (int i = 1; i <= 2 * k; ++i) {
                cout << i << ' ' << i + 1 << "\n";
            }
            cout << 2 * k + 2 << ' ' << 3 << "\n";
            for (int i = 2 * k + 3; i <= n; ++i) {
                cout << i << ' ' << 2 * k + 2 << "\n";
            }
        }
    } else if (n % 3 == 0) {
        int k = n / 3;
        for (int i = 1; i <= 2 * k; ++i) {
            cout << i << ' ' << i + 1 << "\n";
        }
        for (int i = 2 * k + 2; i <= n; ++i) {
            cout << i << ' ' << (i - 2 * k - 1) * 2 << "\n";
        }
    } else {
        int k = (n + 1) / 3;
        for (int i = 1; i <= 2 * k - 1; ++i) {
            cout << i << ' ' << i + 1 << "\n";
        }
        for (int i = 2 * k + 1; i <= n; ++i) {
            cout << i << ' ' << (i - 2 * k) * 2 << "\n";
        }
    }
}

int main () {
    cin.tie(nullptr), cout.tie(nullptr) -> sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}