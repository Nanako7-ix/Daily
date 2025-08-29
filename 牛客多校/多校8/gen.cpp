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
    cout << (1 << 10) << "\n";
    for (int msk = 0; msk < (1 << 10); ++msk) {
        cout << msk << ' ' << popcount<u32>(msk) << ' ' << 1 << "\n";
        for (int i = 0; i < 10; ++i) {
            if (msk >> i & 1) {
                cout << i << " ";
            }
        }
        cout << "\n";
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