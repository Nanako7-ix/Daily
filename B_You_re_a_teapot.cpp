#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

double f(string s) {
    if (s[0] != 't' || s.back() != 't') {
        return 0.0;
    }
    int x = 0, n = s.size();
    for (int i = 0; i < n; ++i) {
        if (s[i] == 't') ++x;
    }
    return 1.0 * (x - 2) / (n - 2);
};

void Thephix() {
    string s;
    cin >> s;

    int n = s.size();
    double ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 3; j <= n - i; ++j) {
            ans = max(ans, f(s.substr(i, j)));
        }
    }

    cout << fixed << setprecision(20) << ans << "\n";
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