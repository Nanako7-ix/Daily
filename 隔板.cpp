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
 * Created: 2025/07/16 13:56:03
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

template<typename m32>
struct Comb {
    int n;
    vector<m32> fact, invfact;
    Comb() : n(0), fact{1}, invfact{1} {}
    void init(int m) {
        if(m <= n) return;
        fact.resize(m + 1);
        invfact.resize(m + 1);
        for(int i = n + 1; i <= m; ++i) {
          fact[i] = fact[i - 1] * i;
        }
        invfact[m] = fact[m].inv();
        for(int i = m; i >= n + 1; --i) {
          invfact[i - 1] = invfact[i] * i;
        }
        n = m;
    }
    m32 fac(int m) {
        if(n < m) init(2 * m);
        return fact[m];
    }
    m32 invfac(int m) {
        if(n < m) init(2 * m);
        return invfact[m];
    }
    m32 inv(int m) {
        return fac(m) * invfac(m - 1);
    }
    m32 C(int n, int m) {
        if(n < m || m < 0) return 0;
        return fac(n) * invfac(m) * invfac(n - m);
    }
    m32 A(int n, int m) {
        if(n < m || m < 0) return 0;
        return fac(n) * invfac(n - m);
    }
};

Comb<m32> comb;

void Meguru() {
    int n, m;
    cin >> n >> m;
    m32 ans = 0;
    for (int i = 0; i < m; ++i) {
        if (i % 2 == 0) {
            ans += comb.C(m, i) * power<m32>(m - i, n);
        } else {
            ans -= comb.C(m, i) * power<m32>(m - i, n);
        }
    }
    cout << ans << "\n";
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