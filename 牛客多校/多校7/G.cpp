#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

std::vector<int> cnt, P;

void sieve(int N) {
    cnt.assign(N + 1, 0);
    P.clear();
    for (int i = 2; i <= N; ++i) {
        if (cnt[i] == 0) {
            cnt[i] = 1;
            P.push_back(i);
        }
        for (i64 p : P) {
            if(i * p > N) break;
            cnt[i * p] = cnt[i] + 1;
            if(i % p == 0) break;
        }
    }
}

void Thephix() {
    int n;
    cin >> n;
    for (int i = 1, j = 1; i <= n && j <= n / 2; ++i) {
        if (cnt[i] % 2 == 1) {
            cout << i << " ";
            ++j;
        }
    }
    cout << '\n';
}

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    sieve(1E6);
    
    int T = 1;
    cin >> T;

    while (T--) {
        Thephix();
    }

    return 0;
}