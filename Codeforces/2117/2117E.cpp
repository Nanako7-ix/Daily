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
    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> b[i];
    }

    multiset<int> Sa, Sb;
    for (int i = n; i >= 0; --i) {
        if (a[i] == b[i] || Sa.contains(a[i]) || Sb.contains(b[i])) {
            cout << i << "\n";
            return;
        }
        if (i != n) {
            Sa.erase(Sa.find(a[i + 1]));
            Sb.erase(Sb.find(b[i + 1]));
            if (Sa.contains(b[i]) || Sb.contains(a[i])) {
                cout << i << "\n"s;
                return;
            }
            Sa.insert(a[i + 1]);
            Sb.insert(b[i + 1]);
        }
        Sa.insert(a[i]);
        Sb.insert(b[i]);
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