#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

i64 inv(vector<int> a) {
    int n = a.size() - 1;
    i64 ans = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j < i; ++j) {
            ans += a[i] < a[j];
        }
    }
    return ans;
}

void Thephix() {
    int id, m, k, n;
    cin >> id >> m >> k >> n;
    for (int i = 1; i <= m; ++i) {
        int ok = 1;
        for (int j = 1; j <= k; ++j) {
            vector<int> a(n * n + 1);
            for (int x = 1; x <= n * n; ++x) {
                cin >> a[x];
            }
            ok &= inv(a) % 2 == 0;
        }
        cout << !ok;
    }
    cout << "\n";
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