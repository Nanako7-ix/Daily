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
    string s, t;
    cin >> n >> m >> s >> t;
    vector<int> a(n + 1);
    for (int i = 1; i <= m; ++i) {
        int l, r;
        cin >> l >> r;
        a[l - 1] ^= 1, a[r] ^= 1;
    }
    for (int i = 0; i < n; ++i) {
        a[i + 1] ^= a[i];
        cout << (a[i] ? t[i] : s[i]);
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