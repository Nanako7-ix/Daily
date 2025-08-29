#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr int K = 2;

void Thephix() {
    int n;
    cin >> n;
    vector<array<int, K + 1>> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < K; ++j) {
            cin >> a[i][j];
        }
        a[i][K] = i;
    }
    
    using iterator = vector<array<int, K + 1>>::iterator;
    [&](this auto&& dfs, iterator l, iterator r, int k) -> void {
        if (l + 1 == r || k == K) return;
        iterator mid = l + (r - l) / 2;
        sort(l, r,
            [k](const array<int, K + 1>& x, const array<int, K + 1>& y) {
                return x[k] < y[k];
            }
        );
        dfs(l, mid, k + 1), dfs(mid, r, k + 1);
    } (a.begin() + 1, a.end(), 0);

    for (int i = 1, j = n; i < j; ++i, --j) {
        cout << a[i][K] << ' ' << a[j][K] << "\n";
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