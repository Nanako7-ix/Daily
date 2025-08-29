#include <bits/stdc++.h>
using namespace std;

vector<int> minp, primes;
void sieve(int n) {
    minp.assign(n + 1, 0);
    for (int i = 2; i <= n; ++i) {
        if (minp[i] == 0) {
            primes.push_back(minp[i] = i);
        }
        for (auto p : primes) {
            if (i * p > n) break;
            minp[i * p] = p;
            if (i % p == 0) break;
        }
    }
}

int main () {
    cin.tie(nullptr), cout.tie(nullptr) -> sync_with_stdio(false);
    int n;
    cin >> n;
    sieve(5000);
    int p = *upper_bound(primes.begin(), primes.end(), n);
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cout << i * p + j << " \n"[j == n];
        }
    }
}