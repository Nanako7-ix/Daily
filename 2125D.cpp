#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

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

using Z = ModInt<u32, 998244353>;

void Thephix() {
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, Z>>> a(m + 1);
    for (int i = 1; i <= n; ++i) {
        int l, r;
        Z p, q;
        cin >> l >> r >> p >> q;
        a[r].emplace_back(l, p / q);
    }

    vector<Z> pre(m + 1, 1);
    for (int i = 1; i <= m; ++i) {
        for (auto [l, p] : a[i]) {
            pre[i] *= 1 - p;
        }
        pre[i] *= pre[i - 1];
    }

    vector<Z> dp(m + 1);
    dp[0] = 1;
    for (int r = 1; r <= m; ++r) {
        for (auto [l, p] : a[r]) {
            dp[r] += p * (pre[r] / pre[l - 1]) / (1 - p) * dp[l - 1];
        }
    }

    cout << dp[m] << "\n";
}

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T = 1;
    // cin >> T;

    while (T--) {
        Thephix();
    }

    return 0;
}