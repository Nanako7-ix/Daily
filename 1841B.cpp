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
    int n, flag = 1;
    cin >> n;
    vector<int> a;
    for (int i = 1; i <= n; ++i) {
        int x; cin >> x;
        if (flag && (i == 1 || x >= a.back())) {
            a.push_back(x);
            cout << 1;
        } else if (flag && x <= a[0]) {
            a.push_back(x);
            cout << 1;
            flag = 0;
        } else if (x >= a.back() && x <= a[0]) {
            a.push_back(x);
            cout << 1;
        } else {
            cout << 0;
        }
    }
    cout << "\n";
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