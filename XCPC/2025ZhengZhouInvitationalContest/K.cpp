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
 * Author:  Thephix
 * Created: 2025/07/14 10:51:58
 * 好想和 めぐる 一起打 xcpc 啊
 */
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr int Tpx = 0;
constexpr int inf = 1E9;
constexpr i64 INF = 4E18;

constexpr int _[10] = {1, 0, 0, 0, 1, 0, 1, 0, 2, 1};

template<typename T>
vector<T> Conv(vector<T> a, vector<T> b) {
    constexpr i64 g = 3, gi = 332748118, p = 998244353;
    auto power = [&](i64 a, i64 b) {
        i64 res = 1;
        for (a %= p; b; a = a * a % p, b >>= 1) {
            if (b & 1) res = res * a % p;
        }
        return res;
    };

    int n = a.size(), m = b.size();
    int N = 1, t = 0;
    while(N < n + m) {
        N <<= 1, ++t;
    }

    a.resize(N), b.resize(N);
    vector<int> rev(N);
    for(int i = 0; i < N; ++i) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (t - 1));
    }
    
    auto ntt = [&](vector<i64>& f, int op) {
        for(int i = 0; i < N; ++i) {
            if(i < rev[i]) swap(f[i], f[rev[i]]);
        }

        for(int i = 1; i < N; i <<= 1) {
            i64 wn = power(op == 1 ? g : gi, (p - 1) / (i << 1));
            for(int j = 0; j < N; j += (i << 1)) {
                for(i64 k = 0, w = 1; k < i; ++k, w = w * wn % p) {
                    i64 fx = f[j + k], fy = w * f[i + j + k] % p;
                    f[j + k] = (fx + fy) % p;
                    f[i + j + k] = (fx - fy + p) % p;
                }
            }
        }
    };
    
    ntt(a, 1), ntt(b, 1);
    for(int i = 0; i < N; ++i) {
        a[i] = a[i] * b[i] % p;
    }
    ntt(a, -1);
    
    const i64 inv = power(N, p - 2);
    vector<T> ans(n + m - 1);
    for(int i = 0; i < n + m - 1; ++i) {
        ans[i] = a[i] * inv % p;
    }

    return ans;
}

void Meguru() {
    int n, m;
    cin >> n >> m;

    vector<i64> hole(m);
    hole[0] = 1;
    for (int i = 0; i < m; ++i) {
        for (int x = i; x; x /= 10) {
            hole[i] += _[x % 10];
        }
    }
    reverse(hole.begin(), hole.end());

    vector<i64> cnt(m);
    for (int i = 1; i <= n; ++i) {
        int x; cin >> x;
        cnt[x]++;
    }

    auto ans = Conv(cnt, hole);
    for (int i = m; i < (int) ans.size(); ++i) {
        ans[i % m] += ans[i];
    }

    i64 Max = 0;
    for (int i = 0; i < m; ++i) {
        Max = max(Max, ans[i]);
    }
    cout << Max << "\n";
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T = 1;
    // cin >> T;

    while (T--) {
        Meguru();
    }

    return Tpx;
}