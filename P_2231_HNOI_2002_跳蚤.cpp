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

template<typename T>
constexpr T power(T a, i64 b, T res = 1) {
    for(; b; b >>= 1, a *= a) {
        if(b & 1) res *= a;
    }
    return res;
}

vector<int> minp, primes;
void sieve(int N) {
    minp.assign(N + 1, 0);
    primes.clear();
    for(int i = 2; i <= N; ++i) {
        if(!minp[i]) primes.emplace_back(minp[i] = i);
        for(auto p : primes) {
            if(i * p > N) break;
            minp[i * p] = p;
            if(i % p == 0) break;
        }
    }
}

void solve() {
    constexpr int N = 1e4;
    sieve(N);

    i64 n, m, _m;
    cin >> n >> m;
    _m = m;
    vector<int> p;
    for(auto pri : primes) {
        if(pri * pri > _m) break;
        if(_m % pri == 0) {
            p.push_back(pri);
            while(_m % pri == 0) {
                _m /= pri;
            }
        }
    }
    if(_m > 1) p.push_back(_m);

    int k = p.size();
    i64 ans = 0;
    for(int i = 0; i < (1 << k); ++i) {
        int popcount = 0, d = 1;
        for(int j = 0; j < k; ++j) {
            if(i >> j & 1) {
                popcount++;
                d *= p[j];
            }
        }
        if(popcount & 1) {
            ans -= power<i64>(m / d, n);
        } else {
            ans += power<i64>(m / d, n);
        }
    }
    cout << ans << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}