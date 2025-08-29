#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

template<u32 Mod> constexpr u32 mulMod(u32 a, u32 b) { return static_cast<u64> (a) * b % Mod; }
template<u64 Mod> constexpr u64 mulMod(u64 a, u64 b) { return static_cast<u128>(a) * b % Mod; }

template<std::unsigned_integral U, U Mod, typename S = std::make_signed_t<U>>
struct ModInt {
public:
    constexpr ModInt() : x(0) {}
    template<std::unsigned_integral T> constexpr ModInt(T v) : x(v % Mod) {}
    template<std::signed_integral T> constexpr ModInt(T v) { S t = v % S(Mod); x = t < 0 ? t + Mod : t; }
    constexpr U val() const { return x; }
    constexpr static int mod() { return Mod; }
    constexpr ModInt operator-() const { return x == 0 ? 0 : Mod - x; }
    constexpr ModInt inv() const { return pow(Mod - 2); }
    constexpr ModInt& operator+=(const ModInt& rhs) & { x += rhs.val(); if(x >= Mod) x -= Mod; return *this; }
    constexpr ModInt& operator-=(const ModInt& rhs) & { x -= rhs.val(); if(x >= Mod) x += Mod; return *this; }
    constexpr ModInt& operator*=(const ModInt& rhs) & { x = mulMod<Mod>(x, rhs.val()); return *this; }
    constexpr ModInt& operator/=(const ModInt& rhs) & { return *this *= rhs.inv(); }
    friend constexpr ModInt operator+(ModInt lhs, const ModInt& rhs) { return lhs += rhs; }
    friend constexpr ModInt operator-(ModInt lhs, const ModInt& rhs) { return lhs -= rhs; }
    friend constexpr ModInt operator*(ModInt lhs, const ModInt& rhs) { return lhs *= rhs; }
    friend constexpr ModInt operator/(ModInt lhs, const ModInt& rhs) { return lhs /= rhs; }
    friend constexpr std::strong_ordering operator<=>(const ModInt &lhs, const ModInt &rhs) = default;
    friend std::istream& operator>>(std::istream& is, ModInt& a) { i64 x; is >> x; a = ModInt(x); return is; }
    friend std::ostream& operator<<(std::ostream& os, const ModInt& a) { os << a.val(); return os; }
    constexpr ModInt pow(i64 b) const { ModInt res = 1, a = *this; for (; b; b >>= 1, a *= a) if (b & 1) res *= a; return res; }
private:
    U x;
};

using Z = ModInt<u32, 998244353>;

constexpr int N = 32;
using mat = array<array<Z, N>, N>;

mat operator*(const mat& x, const mat& y) {
    mat res {};
    for (int i = 0; i < N; ++i) {
        for (int k = 0; k < N; ++k) {
            for (int j = 0; j < N; ++j) {
                res[i][j] += x[i][k] * y[k][j];
            }
        }
    }
    return res;
}

mat power(mat a, i64 b) {
    mat res {};
    for (int i = 0; i < N; ++i) {
        res[i][i] = 1;
    }
    for (; b; a = a * a, b >>= 1) {
        if (b & 1) res = res * a;
    }
    return res;
}

void Thephix() {
    i64 n, k;
    cin >> n >> k;

    mat f {};
    array<Z, N> g {};
    for (int i = 1; i <= k; ++i) {
        int x; cin >> x;
        g[x] = Z(x) / k, g[x + 16] = Z(k).inv();
        for (int mask = 0; mask < 16; ++mask) {
            // (+) dp[(mask + x) % 16] += (1/5k) * (dp[mask] + x * p[mask])
            // (+)  p[(mask + x) % 16] += (1/5k) * p[mask]
            f[(mask + x) % 16][mask] += Z(5 * k).inv();
            f[(mask + x) % 16][mask + 16] += Z(x) / Z(5 * k);
            f[(mask + x) % 16 + 16][mask + 16] += Z(5 * k).inv();

            // (*) dp[(mask * x) % 16] += (x/5k) * dp[mask]
            // (*)  p[(mask * x) % 16] += (1/5k) *  p[mask]
            f[(mask * x) % 16][mask] += Z(x) / Z(5 * k);
            f[(mask * x) % 16 + 16][mask + 16] += Z(5 * k).inv();

            // (&) dp[mask & x] += (1/5k) * p[mask] * (mask & x)
            // (&)  p[mask & x] += (1/5k) * p[mask]
            f[(mask & x)][mask + 16] += Z(mask & x) / Z(5 * k);
            f[(mask & x) + 16][mask + 16] += Z(5 * k).inv();

            // (|) dp[mask | x] += (1/5k) * (dp[mask] + ((mask | x) - mask) * p[i - 1][mask])
            // (|)  p[mask | x] += (1/5k) * p[mask]
            f[(mask | x)][mask] += Z(5 * k).inv();
            f[(mask | x)][mask + 16] += Z((mask | x) - mask) / Z(5 * k);
            f[(mask | x) + 16][mask + 16] += Z(5 * k).inv();

            // (^) dp[mask ^ x] += (1/5k) * (dp[mask] + ((mask ^ x) - mask) * p[i - 1][mask])
            // (^)  p[mask ^ x] += (1/5k) * p[mask]
            f[(mask ^ x)][mask] += Z(5 * k).inv();
            f[(mask ^ x)][mask + 16] += Z((mask ^ x) - mask) / Z(5 * k);
            f[(mask ^ x) + 16][mask + 16] += Z(5 * k).inv();
        }
    }

    f = power(f, n - 1);

    Z ans = 0;
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < N; ++j) {
            ans += f[i][j] * g[j];
        }
    }
    cout << ans << "\n";
}

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T = 1;
    cin >> T;

    while (T--) {
        Thephix();
    }

    return 0;
}