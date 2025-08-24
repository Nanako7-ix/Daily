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
    vector<i64> f(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> f[i];
    }
    i64 Max = -1E18;
    for (int i = 1; i <= n; ++i) {
        i64 x; cin >> x;
        f[i] -= x;
        Max = max(Max, f[i]);
    }

    vector<int> p;
    for (int i = 1; i <= n; ++i) {
        if (f[i] == Max) {
            p.push_back(i);
        }
    }
    
    cout << p.size() << "\n";
    for (auto x : p) {
        cout << x << ' ';
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