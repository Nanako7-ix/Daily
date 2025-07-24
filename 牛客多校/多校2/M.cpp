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

void Thephix () {
    string l, s;
    cin >> l >> s;
    reverse(l.begin(), l.end());
    reverse(s.begin(), s.end());

    vector dp (s.size() + 1, array<array<array<array<array <Z, 3>, 2>, 2>, 2>, 2> { });
    vector vis(s.size() + 1, array<array<array<array<array <int, 3>, 2>, 2>, 2>, 2> { });
    auto dfs = [&](auto&& dfs, int p, bool lima, bool limb, bool limc, bool liml, int dis) -> Z {
        if (dis < -1) return 0;
        dis = min(dis, 1);
        if (p == 0) return (dis > 0) * (1 + (!lima && !limb));
        if (vis[p][lima][limb][limc][liml][dis + 1] == 0) {
            vis[p][lima][limb][limc][liml][dis + 1] = 1;
            for (int c = 0; c <= (!limc || s[p - 1] == '1'); ++c) {
                for (int b = 0; b <= (!limb || c == 1); ++b) {
                    for (int a = 0; a <= (!lima || b == 1); ++a) {
                        int add = (p > (int) l.size() ? 0 : l[p - 1] - '0') - (a ^ b ^ c);
                        if (liml == 1 && add < 0) continue;
                        dp[p][lima][limb][limc][liml][dis + 1] += dfs (
                            dfs,
                            p - 1,
                            lima && a == b,
                            limb && b == c,
                            limc && c == s[p - 1] - '0',
                            liml && add == 0,
                            (dis << 1) + a + b - c
                        );
                    }
                }
            }
        }
        return dp[p][lima][limb][limc][liml][dis + 1];
    };

    cout << dfs(dfs, s.size(), 1, 1, 1, l.size() <= s.size(), 0) << "\n";
}

int main () {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T = 1;
    cin >> T;

    while (T--) {
        Thephix();
    }

    return 0;
}