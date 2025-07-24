#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr i64 K = 1E6;

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


namespace pcf {
    constexpr int MAXN = 100;       // pre-calc max n for phi(m, n)
    constexpr int MAXM = 10010;     // pre-calc max m for phi(m, n)
    constexpr int MAXP = 50000000;  // max primes counter
    constexpr int MAX  = 400010;    // max prime
    #define setbit(ar, i) (((ar[(i) >> 6]) |= (1 << (((i) >> 1) & 31))))
    #define chkbit(ar, i) (((ar[(i) >> 6]) & (1 << (((i) >> 1) & 31))))
    #define isprime(x)    (((x) && ((x) & 1) && (!chkbit(ar, (x)))) || ((x) == 2))

    i64 dp[MAXN][MAXM];
    u32 ar[(MAX >> 6) + 5] = { 0 };
    int len = 0, primes[MAXP], counter[MAX];
  
    void Sieve() {
        setbit(ar, 0);
        setbit(ar, 1);
        for (int i = 3; (i * i) < MAX; i++, i++) {
            if (!chkbit(ar, i)) {
                int k = i << 1;
                for (int j = (i * i); j < MAX; j += k) {
                    setbit(ar, j);
                }
            }
        }
  
        for (int i = 1; i < MAX; i++) {
            counter[i] = counter[i - 1];
            if (isprime(i)) primes[len++] = i, counter[i]++;
        }
    }
  
    void init() {
        Sieve();
        for (int n = 0; n < MAXN; n++) {
            for (int m = 0; m < MAXM; m++) {
                if (!n) dp[n][m] = m;
                else dp[n][m] = dp[n - 1][m] - dp[n - 1][m / primes[n - 1]];
            }
        }
    }
  
    i64 phi(i64 m, int n) {
        if (n == 0) return m;
        if (primes[n - 1] >= m) return 1;
        if (m < MAXM && n < MAXN) return dp[n][m];
        return phi(m, n - 1) - phi(m / primes[n - 1], n - 1);
    }
  
    i64 Lehmer(i64 m) {
        if (m < MAX) return counter[m];
  
        int c = cbrt(0.9 + m), x = c, a = counter[x], s = sqrt(0.9 + m);
        i64 res = phi(m, a) + a - 1;
        for (int i = a; primes[i] <= s; i++) {
            res = res - Lehmer(m / primes[i]) + Lehmer(primes[i]) - 1;
        }
        return res;
    }
}

template<std::unsigned_integral T>
T lower_sqrt (T n) {
    T t = sqrt(n);
    while (t * t > n) --t;
    while ((t + 1) * (t + 1) < n) ++t;
    return t;
}

template<std::unsigned_integral T>
T upper_sqrt (T n) {
    T t = sqrt(n);
    while (t * t < n) ++t;
    while ((t - 1) * (t - 1) >= n) --t;
    return t;
}

i64 solve (i64 n) {
    i64 ans = 0;
    for (auto p : P) {
        i64 lim = (n + p) / (1LL * p * p);
        if (lim == 0) break;
        ans += lower_sqrt<u64> (lim);
    }
    for (i64 i = 1; true; ++i) {
        i64 l = 1, r = 1E9, res = -1;
        while (l <= r) {
            i64 mid = (l + r) >> 1;
            if (i * i <= (n + mid) / (mid * mid)) {
                res = mid, l = mid + 1;
            } else r = mid - 1;
        }
        if (res == -1) break;
        i64 cnt = max(pcf::Lehmer(res) - (int) P.size(), 0LL);
        if (cnt == 0) break;
        ans += cnt;
    }
    return ans;
}

void Thephix() {
    pcf::init();
    sieve(K);
    i64 l, r;
    cin >> l >> r;
    cout << solve(r) - solve(l - 1) << "\n";
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