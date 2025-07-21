#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr i64 power(i64 a, i64 b, i64 p) {
    i64 res = 1;
    for (a %= p; b; b >>= 1, a = a * a % p) {
        if (b & 1) res = res * a % p;
    }
    return res;
}

void Thephix() {
    i64 b, c, p;
    cin >> b >> c >> p;

    vector<int> a { 114514 } , vis(p);
    for (int x = power(b, c, p); !vis[x]; x = power(b, x, p)) {
        a.push_back(x);
        vis[x] = a.size() - 1;
    }

    int len1 = vis[power(b, a.back(), p)] - 1;
    int len2 = a.size() - 1 - len1;

    vector<int> init { 0 }, cir;
    for (int i = 1; i < (int) a.size(); ++i) {
        (i <= len1 ? init : cir).push_back(a[i]);
    }
    for (int i = 1; i <= len1; ++i) {
        init[i] += init[i - 1];
        init[i] %= p;
    }
    for (int i = 1; i < len2; ++i) {
        cir[i] += cir[i - 1];
        cir[i] %= p;
    }

    int q;
    cin >> q;
    while (q--) {
        i64 k;
        cin >> k;

        if (k <= len1) {
            cout << init[k] << "\n";
            continue;
        }

        i64 res = init.back();
        k -= len1;

        i64 cnt = ((k - 1) / len2) % p;
        res += cnt * cir.back() % p;
        res += cir[(k - 1) % len2];

        cout << res % p << "\n";
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