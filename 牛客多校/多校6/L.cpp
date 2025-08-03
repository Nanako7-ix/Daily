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
    vector<array<int, 2>> a(m + 1);
    for (int i = 1; i <= m; ++i) {
        cin >> a[i][0] >> a[i][1];
    }
    sort(a.begin() + 1, a.end(), [](const array<int, 2>& x, const array<int, 2>& y) {
        return x[1] > y[1];
    });
    
    string s(2 * n + 1, '(');
    for (int i = n + 1; i <= 2 * n; ++i) {
        s[i] = ')';
    }
    
    for (int i = 1, j = n, Max = -1; i <= m; ++i) {
        auto [l, r] = a[i];
        if (r < Max) {
            if (j <= 0) {
                cout << "-1\n";
                return;
            }
            swap(s[j], s[Max]);
            j--, Max = -1;
        }
        Max = max(Max, l);
        if (i == m) {
            if (j <= 0) {
                cout << "-1\n";
                return;
            }
            swap(s[j], s[Max]);
            j--, Max = -1;
        }
    }
    
    auto check = [&]() -> bool {
        vector<int> f(2 * n + 1);
        for (int i = 1; i <= 2 * n; ++i) {
            f[i] = s[i] == ')' ? -1 : 1;
            f[i] += f[i - 1];
            if (f[i] < 0) return false;
        }
        return true;
    };
    
    if (check()) {
        cout << s.substr(1) << "\n";
    } else {
        cout << "-1\n";
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