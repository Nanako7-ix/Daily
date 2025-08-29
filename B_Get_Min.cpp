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
    int n; cin >> n;
    multiset<int> s;
    for (int i = 1; i <= n; ++i) {
        int op; cin >> op;
        if (op == 1) {
            int x; cin >> x;
            s.insert(x);
        } else {
            cout << *s.begin() << "\n";
            s.erase(s.begin());
        }
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