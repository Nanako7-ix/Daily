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
    vector<i64> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.end());

    vector<array<int, 2>> tr(2);
    for (int i = 1; i <= n; ++i) {
        // Min
        if (i != 1) {
            i64 ans = 0;
            for (int k = 60, p = 1; k >= 0; --k) {
                int x = a[i] >> k & 1;
                if (tr[p][x]) {
                    p = tr[p][x];
                } else {
                    ans |= 1LL << k;
                    p = tr[p][x ^ 1];
                }
            }
            if (ans < a[i]) {
                cout << "NO\n";
                return;
            }
        }
        // insert
        for (int k = 60, p = 1; k >= 0; --k) {
            int x = a[i] >> k & 1;
            if (tr[p][x] == 0) {
                tr[p][x] = tr.size();
                tr.push_back({});
            }
            p = tr[p][x];
        }
    }
    cout << "YES\n";
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