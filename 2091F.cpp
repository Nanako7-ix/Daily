// Author: Nanako7_ix
// Created: 2025/03/25 23:49:24
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

template<u32 Mod>
constexpr u32 mulMod(u32 a, u32 b) {
    return static_cast<u64>(a) * b % Mod;
}

template<u64 Mod>
constexpr u64 mulMod(u64 a, u64 b) {
    return static_cast<u128>(a) * b % Mod;
}

template<unsigned_integral U, U Mod>
struct ModInt {
public:
    constexpr ModInt() : x(0) {}
    template<unsigned_integral T>
    constexpr ModInt(T v) : x(v % Mod) {}
    template<signed_integral T>
    constexpr ModInt(T v) { using S = make_signed_t<U>; S t = v % S(Mod); if (t < 0) t += Mod; x = t; }
    constexpr U val() const { return x; }
    constexpr static int mod() { return Mod; }
    constexpr ModInt operator-() const { return x == 0 ? 0 : Mod - x; }
    constexpr ModInt inv() const { return power(*this, Mod - 2); }
    constexpr ModInt& operator+=(const ModInt& rhs) & { x += rhs.val(); if(x >= Mod) x -= Mod; return *this; }
    constexpr ModInt& operator-=(const ModInt& rhs) & { x -= rhs.val(); if(x >= Mod) x += Mod; return *this; }
    constexpr ModInt& operator*=(const ModInt& rhs) & { x = mulMod<Mod>(x, rhs.val()); return *this; }
    constexpr ModInt& operator/=(const ModInt& rhs) & { return *this *= rhs.inv(); }
    friend constexpr ModInt operator+(ModInt lhs, const ModInt& rhs) { return lhs += rhs; }
    friend constexpr ModInt operator-(ModInt lhs, const ModInt& rhs) { return lhs -= rhs; }
    friend constexpr ModInt operator*(ModInt lhs, const ModInt& rhs) { return lhs *= rhs; }
    friend constexpr ModInt operator/(ModInt lhs, const ModInt& rhs) { return lhs /= rhs; }
    friend constexpr strong_ordering operator<=>(const ModInt &lhs, const ModInt &rhs) = default;
    friend istream& operator>>(istream& is, ModInt& a) { i64 x; is >> x; a = ModInt(x); return is; }
    friend ostream& operator<<(ostream& os, const ModInt& a) { os << a.val(); return os; }
private:
    U x;
};

using m32 = ModInt<u32, 998244353>;

void solve() {
    int n, m, d;
    cin >> n >> m >> d;
    vector<vector<int>> a(n + 1, vector<int> (m + 1));
    for(int i = 1; i <= n; ++i) {
        string s; cin >> s;
        for(int j = 1; j <= m; ++j) {
            a[i][j] = s[j - 1] == 'X';
        }
    }

    vector<vector<m32>> dp(n + 1, vector<m32> (m + 1));
    for(int i = n; i >= 1; --i) {
        if(i == n) {
            for(int j = 1; j <= m; ++j) {
                dp[i][j] = a[i][j];
            }
        } else {
            vector<m32> pre = dp[i + 1];
            for(int j = 1; j <= m; ++j) {
                pre[j] += pre[j - 1];
            }
            for(int j = 1; j <= m; ++j) {
                if(a[i][j] == 0) continue;
                int l = max(1, j - d + 1), r = min(m, j + d - 1);
                dp[i][j] = pre[r] - pre[l - 1];
            }
        }

        vector<m32> pre = dp[i];
        for(int j = 1; j <= m; ++j) {
            pre[j] += pre[j - 1];
        }
        for(int j = 1; j <= m; ++j) {
            if(a[i][j] == 0) continue;
            int l = max(1, j - d), r = min(m, j + d);
            dp[i][j] = pre[r] - pre[l - 1];
        }
    }

    m32 ans = 0;
    for(int i = 1; i <= m; ++i) {
        ans += dp[1][i];
    }
    cout << ans << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}