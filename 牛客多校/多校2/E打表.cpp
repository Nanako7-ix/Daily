#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

std::vector<int> minp, P;

void sieve(int N) {
    minp.assign(N + 1, 0);
    P.clear();
    for (int i = 2; i <= N; ++i) {
        if (minp[i] == 0) {
            P.push_back(minp[i] = i);
        }
        for (i64 p : P) {
            if(i * p > N) break;
            minp[i * p] = p;
            if(i % p == 0) break;
        }
    }
}

std::vector<int> interval_sieve(i64 l, i64 r) {
    assert (l + 1 <= r);
    std::vector<int> ok(r - l + 1, 1);
    if (l == 1) ok[0] = 0;
    for (i64 p : P) {
        i64 s = std::max(p * p, (l + p - 1) / p * p);
        for (i64 i = s; i <= r; i += p) {
            ok[i - l] = 0;
        }
    }
    return ok;
}

int ans[2000];
constexpr int B = 1E6;

void Thephix() {
    sieve(1E5);
    for (int i = 0; i < 2000; ++i) {
        i64 L = 1 + i * B;
        i64 R = (1 + i) * B;
        auto ok = interval_sieve(L, R);
        ans[i] = accumulate(ok.begin(), ok.end(), 0);
        if (i != 0) ans[i] += ans[i - 1];
        cout << ans[i] << ", ";
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