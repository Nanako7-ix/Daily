#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;

vector<int> primes, minp;
void sieve(int n) {
    minp.assign(n + 1, 0);
    for (int i = 2; i <= n; ++i) {
        if (minp[i] == 0) {
            primes.push_back(minp[i] = i);
        }
        for (auto j : primes) {
            if (i * j > n) break;
            minp[i * j] = j;
            if (i % j == 0) break;
        }
    }
}

bool check (i64 n) {
    i64 t = sqrt(n);
    if (t * t == n) return true;
    return false; 
}

void solve () {
    i64 n;
    cin >> n;
    
    vector<i64> p;
    i64 N = n;
    for (auto j : primes) {
        while (N % j == 0) {
            N /= j;
            if (!p.empty() && p.back() == j) {
                p.pop_back();
            } else {
                p.push_back(j);
            }
        }
    }
    if (N != 1) p.push_back(N);

    vector<i64> op;
    for (auto x : p) {
        while (!has_single_bit<u64>(x)) {
            op.push_back(n / x);
            n += n / x;
            x++;
            x >>= countr_zero<u64>(x);
        }
    }

    if (!check(n)) op.push_back(n);
    cout << op.size() << "\n";
    for (auto x : op) {
        cout << x << ' ';
    }
    cout << "\n";
}

int main () {
    cin.tie(nullptr), cout.tie(nullptr) -> sync_with_stdio(false);
    int T;
    cin >> T;
    sieve(1E6);
    while (T--) {
        solve();
    }
    return 0;
}