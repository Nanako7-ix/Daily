#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#define setpre(x) fixed << setprecision(x)
#define debug(x) cerr << #x << " = " << x << "\n"
#define endl "\n"
using namespace std;
using namespace __gnu_pbds;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

constexpr int inf = 0x3f3f3f3f;
constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;

// d     |   2   | f(i) + 1
// sigma | 1 + i | f(i) + ip
// phi   | i - 1 | f(i) * p
// mu    |   -1  | 0
vector<int> minp, primes, mu;
void sieve(int n) {
    minp.assign(n + 1, 0);
    primes.clear();
    mu.assign(n + 1, 0);
    mu[1] = 1;

    vector<i64> g(n + 1, 0);
    for(int i = 2; i <= n; ++i) {
        if(!minp[i]) {
            minp[i] = i;
            g[i] = i, mu[i] = -1;
            primes.push_back(i);
        }
        for(auto p : primes) {
            if(i * p > n) break;
            minp[i * p] = p;
            g[i * p] = p * (i % p ? 1 : g[i]);
            if(i * p == g[i * p]) mu[i * p] = 0;
            else mu[i * p] = mu[g[i * p]] * mu[i * p / g[i * p]];
            if(i % p == 0) break;
        }
    }
    for(int i = 1; i <= n; ++i) {
        mu[i] += mu[i - 1];
    }
}

i64 calc(int n, int m) {
    i64 ans = 0;
    for(int k = 1; k <= min(n, m); ++k) {
        i64 l = k, r = min(n / (n / k), m / (m / k));
        ans += 1ll * (mu[r] - mu[l - 1]) * (n / k) * (m / k);
        k = r;
    }
    return ans;
}

void solve() {
    int n, m;
    cin >> n >> m;
    sieve(min(n, m));
    i64 ans = 0;
    for(int d = 1; d <= min(n, m); ++d) {
        i64 l = d, r = min(n / (n / d), m / (m / d));
        ans += (l + r) * (r - l + 1) / 2 * calc(n / d, m / d);
        d = r;
    }
    cout << 2 * ans - 1ll * n * m << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}