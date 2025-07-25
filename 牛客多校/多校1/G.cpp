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
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;

    while (q--) {
        int p; string t, r;
        cin >> t >> p;
        r = s.substr(p - 1);
        i64 ans = 0, now = 0;
        for (int i = 0; i < (int) t.size(); ++i) {
            if (t[i] != r[i]) {
                ans += (now + 1) * now / 2;
                now = 0;
            } else {
                now++;
            }
        }
        cout << ans + (now + 1) * now / 2 << "\n";
    }
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T = 1;
    // cin >> T;

    while (T--) {
        Thephix();
    }

    return 0;
}