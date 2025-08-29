#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr u32 U = (1 << 30) - 1;


void Thephix() {
    int n, A, B, C;
    cin >> n >> A >> B >> C;

    array<u32, 3> a;
    a[0] = A & U, a[1] = B & U, a[2] = C & U;
    auto gen = [&]() -> u32 {
        u32 g = a[0] ^ ((a[0] << 16) & U);
        u32 h = g ^ (g >> 5);
        u32 f = h ^ ((h << 1) & U) ^ a[1] ^ a[2];
        a = { a[1], a[2], f };
        return f;
    };
    
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int x = gen() % (n - i);
        ans ^= x != 0;
    }
    cout << ans;
    for (int i = 1; i < n; ++i) {
        int l = gen() % n;
        int r = gen() % n;
        int d = gen() % n + 1;
        if (l > r) swap(l, r);
        ans ^= (r - l) & d & 1;
        cout << ans;
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