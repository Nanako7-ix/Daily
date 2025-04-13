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

namespace PollardRho {
    i64 mul(i64 a, i64 b, i64 m) {
        return static_cast<i128>(a) * b % m;
    }
    
    i64 power(i64 a, i64 b, i64 m) {
        i64 res = 1 % m;
        for(; b; b >>= 1, a = mul(a, a, m)) {
            if(b & 1) res = mul(res, a, m);
        }
        return res;
    }
    
    bool isPrime(i64 n) {
        if(n < 2) return false;
        static constexpr int A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
        int s = __builtin_ctzll(n - 1);
        i64 d = (n - 1) >> s;
        for(auto a : A) {
            if(a == n) return true;
            i64 x = power(a, d, n);
            if(x == 1 || x == n - 1) continue;
            bool ok = false;
            for (int i = 1; i < s; ++i) {
                x = mul(x, x, n);
                if(x == n - 1) {
                    ok = true;
                    break;
                }
            }
            if(!ok) return false;
        }
        return true;
    }

    vector<i64> factorize(i64 n) {
        vector<i64> p;
        function<void(i64)> f = [&](i64 n) {
            if(n <= 10000) {
                for(int i = 2; i * i <= n; ++i) {
                    for(; n % i == 0; n /= i) {
                        p.push_back(i);
                    }
                }
                if(n > 1) p.push_back(n);
                return;
            }
            if (isPrime(n)) {
                p.push_back(n);
                return;
            }
            auto g = [&](i64 x) {
                return (mul(x, x, n) + 1) % n;
            };
            for(i64 i = 2; ; ++i) {
                i64 x = i, y = i, d = 1, power = 1, lam = 0, v = 1;
                while(d == 1) {
                    y = g(y), ++lam;
                    v = mul(v, abs(x - y), n);
                    if(lam % 127 == 0) {
                        d = gcd(v, n), v = 1;
                    }
                    if(power == lam) {
                        x = y, power *= 2, lam = 0, d = gcd(v, n), v = 1;
                    }
                }
                if(d != n) {
                    f(d), f(n / d);
                    return;
                }
            }
        };
        f(n);
        sort(p.begin(), p.end());
        return p;
    }
}

void solve() {
    i64 n;
    cin >> n;
    if(n == 1) {
        cout << "-1\n";
    } else {
        auto fac = PollardRho::factorize(n);
        vector<int> cnt;
        cnt.push_back(1);
        for(int i = 1; i < (int) fac.size(); ++i) {
            if(fac[i] == fac[i - 1]) {
                cnt.back()++;
            } else cnt.push_back(1);
        }
        fac.erase(unique(fac.begin(), fac.end()), fac.end());
        i64 x = -1, y = -1;

        auto chk = [&](i128 k) -> i128 {
            i128 l = 1, r = 1000000000, res = -1;
            while(l <= r) {
                i128 m = (l + r) >> 1;
                if(3 * k * m * m + 3 * k * k * m + k * k * k <= n) {
                    res = m, l = m + 1;
                } else r = m - 1;
            }
            if(3 * k * res * res + 3 * k * k * res + k * k * k == n) return res;
            return -1;
        };

        auto dfs = [&](auto &&dfs, i128 k, int p) -> void {
            if(k > 4 * n || k * k > 4 * n || k * k * k > 4 * n) return;
            if(p == (int) fac.size()) {
                assert(n % k == 0);
                i64 t = chk(k);
                if(t != -1) {
                    x = t + k, y = t;
                }
                return;
            }
            for(int i = 0; i <= cnt[p]; ++i) {
                dfs(dfs, k, p + 1);
                if(x != -1) return;
                k *= fac[p];
                if(k > 4 * n || k * k > 4 * n || k * k * k > 4 * n) break;
            }
        };
        dfs(dfs, 1, 0);
        if(x == -1) cout << "-1\n";
        else cout << x << ' ' << y << endl;
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}