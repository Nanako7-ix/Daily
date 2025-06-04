/**
 * Author:  Nanako7_ix
 * Created: 2025/05/10 17:12:36
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


void solve() {
    i64 x, y;
    cin >> x >> y;
    if (x < y) swap(x, y);
    
    vector<array<array<m32, 2>, 2>> dp(35);
    vector<array<array<bool, 2>, 2>> vis(35);
    bitset<35> nx(x), ny(y);

    auto f = [&](i64 val) -> m32 {
        auto dfs = [&](auto &&dfs, int p, bool lx, bool ly) -> m32 {
            if (p == 0) return 1;
            if (vis[p][lx][ly]) {
                return dp[p][lx][ly];
            }

            int Mx = lx ? nx[p - 1] : 1;
            int My = ly ? ny[p - 1] : 1;

            m32 ans = 0;
            for (int i = 0; i <= Mx; ++i) {
                for (int j = 0; j <= My; ++j) {
                    if (i & j) continue;
                    ans += dfs(dfs, p - 1, lx && i == Mx, ly && j == My);
                }
            }

            vis[p][lx][ly] = 1;
            dp[p][lx][ly] = ans;
            return ans;
        };
        return dfs(dfs, __lg(val) + 1, x < val, y < val);
    };

    m32 ans = 0, lst = 1;
    for (i64 i = 2; __lg(i - 1) <= __lg(x); i *= 2) {
        m32 cnt = f(i - 1);
        ans += __lg(i) * (cnt - lst);
        lst = cnt;
    }
    cout << ans << endl;
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
    
    int T = 1;
    cin >> T;
    
    while (T--) {
        solve();
    }
    
    return 0;
}