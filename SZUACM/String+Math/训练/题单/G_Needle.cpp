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
 * Created: 2025/05/20 21:21:34
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

constexpr int inf = 0x3f3f3f3f;
constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;
constexpr int offset = 30000;
constexpr int N = 60000;

constexpr i64 power(i64 a, i64 b, i64 Mod) {
    i64 res = 1;
    for(; b; b >>= 1, (a *= a) %= Mod) {
        if(b & 1) (res *= a) %= Mod;
    }
    return res;
}

constexpr i64 g = 3, gi = 332748118, p = 998244353;
vector<i64> convolotion(vector<i64> a, vector<i64> b) {
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
            if(i < rev[i]) {
                swap(f[i], f[rev[i]]);
            }
        }

        for(int i = 1; i < N; i <<= 1) {
            i64 wn = power(op == 1 ? g : gi, (p - 1) / (i << 1), p);
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

    vector<i64> ans(n + m - 1);
    i64 inv = power(N, p - 2, p);
    for(int i = 0; i < n + m - 1; ++i) {
        ans[i] = a[i] * inv % p;
    }
    return ans;
}

void solve() {
    int n;
    vector<i64> f1(N + 1), f2(N + 1), f3(N + 1);

    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int x; cin >> x;
        x += offset;
        f1[x]++;
    }
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int x; cin >> x;
        x += offset;
        f2[x]++;
    }
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int x; cin >> x;
        x += offset;
        f3[x]++;
    }

    auto f = convolotion(f1, f3);
    i64 ans = 0;
    for (int i = 1; i <= N; ++i) {
        ans += f[2 * i] * f2[i];
    }
    cout << ans << endl;
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