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
    if (k % 2 == 1) {
        cout << "-1\n";
        return;
    }

    k /= 2;
    vector<vector<int>> a(n + 1, vector<int> (n + 1));
    for (int i = 1; i <= k; ++i) {
        a[i][i] = 1;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cout << a[i][j];
        }
        cout << "\n";
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