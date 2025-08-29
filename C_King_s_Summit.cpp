#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr i64 inf = 4E18;

void Thephix() {
    int n;
    cin >> n;
    i64 Minx = inf, Maxx = 0;
    i64 Miny = inf, Maxy = 0;
    for (int i = 1; i <= n; ++i) {
        i64 x, y;
        cin >> x >> y;
        Minx = min(Minx, x), Maxx = max(Maxx, x);
        Miny = min(Miny, y), Maxy = max(Maxy, y);
    }
    cout << max((Maxx - Minx + 1) / 2, (Maxy - Miny + 1) / 2) << "\n";
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