/**
 *
 *  $$$$$$\  $$$$$$\  $$$$$$\  $$\       $$\       $$$$$$\  
 * $$  __$$\ \_$$  _|$$  __$$\ $$ |      $$ |     $$  __$$\ 
 * $$ /  \__|  $$ |  $$ /  $$ |$$ |      $$ |     $$ /  $$ |
 * $$ |        $$ |  $$$$$$$$ |$$ |      $$ |     $$ |  $$ |
 * $$ |        $$ |  $$  __$$ |$$ |      $$ |     $$ |  $$ |
 * $$ |  $$\   $$ |  $$ |  $$ |$$ |      $$ |     $$ |  $$ |
 *  $$$$$$ | $$$$$$\ $$ |  $$ |$$$$$$$$\ $$$$$$$$\ $$$$$$  |
 * \______/  \______|\__|  \__|\________|\________|\______/ 
 *
 * Author:  Nanako7_ix
 * Created: 2025/06/28 20:59:55
 * 好想和 めぐる 一起打 xcpc 啊
 */
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
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
using f64 = double;

constexpr int inf = 0x3f3f3f3f;
constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;

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
    static constexpr int A[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
    int s = countr_zero<u64> (n - 1);
    i64 d = (n - 1) >> s;
    for (auto a : A) {
        if (a == n) return true;
        i64 x = power(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool ok = false;
        for (int i = 1; i < s; ++i) {
            x = mul(x, x, n);
            if (x == n - 1) {
                ok = true;
                break;
            }
        }
        if(!ok) return false;
    }
    return true;
}

vector<int> minp, primes;
void sieve(int N) {
    minp.assign(N + 1, 0);
    primes.clear();
    for (i64 i = 2; i <= N; ++i) {
        if (!minp[i]) primes.emplace_back(minp[i] = i);
        for (auto p : primes) {
            if (i * p > N) break;
            minp[i * p] = p;
            if (i % p == 0) break;
        }
    }
}

void solve() {
    sieve(1E7);
    
    i64 l, r;
    cin >> l >> r;
    
    int ans = 1;
    
    auto cnt = [](i64 x, i64 p) {
        i64 res = 1, ans = 0;
        while (i128(res) * p <= x) {
            res *= p, ans++;
        }
        return ans;
    };

    for (auto p : primes) {
        if (p > r) break;
        ans += cnt(r, p) - max(cnt(l, p), 1LL);
    }

    for (i64 i = l % 2 == 0 ? l + 1 : l + 2; i <= r; i += 2) {
        ans += isPrime(i);
    }

    cout << ans << "\n";
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T = 1;
    // cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}