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
 * Created: 2025/07/10 20:43:04
 * 好想和 めぐる 一起打 xcpc 啊
 */
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define debug(x) cerr << "\033[31m" << #x << " = " << x << "\033[0m\n"
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

using m32 = ModInt<u32, 1000000007>;

struct Matrix : array<array<m32, 3>, 3> {
    Matrix () {
        (*this)[0][0] = 1;
        (*this)[0][1] = 0;
        (*this)[0][2] = 0;
        (*this)[1][0] = 0;
        (*this)[1][1] = 1;
        (*this)[1][2] = 0;
        (*this)[2][0] = 0;
        (*this)[2][1] = 0;
        (*this)[2][2] = 1;
    }
    Matrix (m32 q) {
        (*this)[0][0] = q;
        (*this)[0][1] = 1 - q;
        (*this)[0][2] = 0;
        (*this)[1][0] = 0;
        (*this)[1][1] = q;
        (*this)[1][2] = 1 - q;
        (*this)[2][0] = 0;
        (*this)[2][1] = 0;
        (*this)[2][2] = 1;
    }

    friend Matrix operator* (const Matrix& a, const Matrix& b) {
        Matrix res;
        res[0][0] = a[0][0] * b[0][0] + a[0][1] * b[1][0] + a[0][2] * b[2][0];
        res[0][1] = a[0][0] * b[0][1] + a[0][1] * b[1][1] + a[0][2] * b[2][1];
        res[0][2] = a[0][0] * b[0][2] + a[0][1] * b[1][2] + a[0][2] * b[2][2];
        res[1][0] = a[1][0] * b[0][0] + a[1][1] * b[1][0] + a[1][2] * b[2][0];
        res[1][1] = a[1][0] * b[0][1] + a[1][1] * b[1][1] + a[1][2] * b[2][1];
        res[1][2] = a[1][0] * b[0][2] + a[1][1] * b[1][2] + a[1][2] * b[2][2];
        res[2][0] = a[2][0] * b[0][0] + a[2][1] * b[1][0] + a[2][2] * b[2][0];
        res[2][1] = a[2][0] * b[0][1] + a[2][1] * b[1][1] + a[2][2] * b[2][1];
        res[2][2] = a[2][0] * b[0][2] + a[2][1] * b[1][2] + a[2][2] * b[2][2];
        return res;
    }

    friend array<m32, 3>& operator*= (array<m32, 3>& a, const Matrix& b) {
        tie(a[0], a[1], a[2]) = make_tuple(
            a[0] * b[0][0] + a[1] * b[1][0] + a[2] * b[2][0],
            a[0] * b[0][1] + a[1] * b[1][1] + a[2] * b[2][1],
            a[0] * b[0][2] + a[1] * b[1][2] + a[2] * b[2][2]
        );
        return a;
    }
};

constexpr Matrix power(Matrix a, i64 b) {
    Matrix res;
    for(; b; b >>= 1, a = a * a) {
        if(b & 1) res = res * a;
    }
    return res;
}

void solve() {
    m32 p, q, r;
    cin >> p >> q >> r;
    p /= 1000, q /= 1000, r /= 1000;
    p = 1 - p, q = 1 - q;

    int n;
    cin >> n;
    
    array<m32, 3> ans {1, 0, 0};
    i64 sum = 0;
    for (int i = 1; i <= n; ++i) {
        ans[2] = (ans[1] * r);
        ans[1] *= 1 - r;
        i64 x; cin >> x;

        i64 y = min(80 - sum, x);
        ans *= power(Matrix(p), y);
        x -= y, sum += y;
        ans *= power(Matrix(p * q), x);

        cout << ans[2] << "\n";
    }
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