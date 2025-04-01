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

i64 exgcd(i64 a, i64 b, i64& x1, i64& y1) {
    x1 = 1, y1 = 0; i64 x2 = 0, y2 = 1;
    if (a < 0) x1 *= -1, a *= -1;
    if (b < 0) y2 *= -1, b *= -1;
    while (b) {
        i64 k = a / b;
        x1 -= k * x2, y1 -= k * y2, a -= k * b;
        swap(x1, x2), swap(y1, y2), swap(a, b);
    }
    return a;
}

struct Barrett {
public:
    Barrett(u32 _m) : m(_m), im((u64)(-1) / _m + 1) {}
    constexpr u32 Mod() const { return m; }
    constexpr u32 mul(u32 a, u32 b) const {
        u64 z = 1LL * a * b;
        u64 x = u64((u128(z) * im) >> 64);
        u32 v = u32(z - x * m);
        if (m <= v) v += m;
        return v;
    }
private:
    u32 m;
    u64 im;
};

template<u32 Id>
struct DynModInt {
public:
    constexpr DynModInt() : x(0) {}
    template<unsigned_integral T>
    constexpr DynModInt(T v) : x(v % Mod()) {}
    template<signed_integral T>
    constexpr DynModInt(T v) { int t = v % int(Mod()); if(t < 0) t += Mod(); x = t; }
    constexpr static void setMod(u32 m) { bt = m; }
    constexpr static u32 Mod() { return bt.Mod(); }
    constexpr u32 val() const { return x; }
    constexpr DynModInt operator-() const { return x == 0 ? 0 : Mod() - x; }
    constexpr DynModInt inv() const { i64 x, y; assert(exgcd(this -> x, Mod(), x, y) == 1); return x; }
    constexpr DynModInt& operator+=(const DynModInt& rhs) & { x += rhs.val(); if(x >= Mod()) x -= Mod(); return *this; }
    constexpr DynModInt& operator-=(const DynModInt& rhs) & { x -= rhs.val(); if(x >= Mod()) x += Mod(); return *this; }
    constexpr DynModInt& operator*=(const DynModInt& rhs) & { x = bt.mul(x, rhs.val()); return *this; }
    constexpr DynModInt& operator/=(const DynModInt& rhs) & { return *this *= rhs.inv(); }
    friend constexpr DynModInt operator+(DynModInt lhs, const DynModInt& rhs) { return lhs += rhs; }
    friend constexpr DynModInt operator-(DynModInt lhs, const DynModInt& rhs) { return lhs -= rhs; }
    friend constexpr DynModInt operator*(DynModInt lhs, const DynModInt& rhs) { return lhs *= rhs; }
    friend constexpr DynModInt operator/(DynModInt lhs, const DynModInt& rhs) { return lhs /= rhs; }
    friend constexpr strong_ordering operator<=> (const DynModInt &lhs, const DynModInt &rhs) = default;
    friend istream& operator>>(istream& is, DynModInt& a) { i64 x; is >> x; a = DynModInt {x}; return is; }
    friend ostream& operator<<(ostream& os, const DynModInt& a) { os << a.val(); return os; }
private:
    u32 x;
    static Barrett bt;
};

template<u32 Id> Barrett DynModInt<Id>::bt = 998244353;

using m32 = DynModInt<0>;

template<typename Z>
struct Comb {
  int n;
  vector<Z> fact, invfact;
  Comb() : n(0), fact{1}, invfact{1} {}
  void init(int m) {
    m = min<int>(m, Z::Mod() - 1);
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
  Z fac(int m) {
    if(n < m) init(2 * m);
    return fact[m];
  }
  Z invfac(int m) {
    if(n < m) init(2 * m);
    return invfact[m];
  }
  Z inv(int m) {
    return invfac(m) * fac(m - 1);
  }
  Z C(int n, int m) {
    if(n < m || m < 0) return 0;
    return fac(n) * invfac(m) * invfac(n - m);
  }
  Z A(int n, int m) {
    if(n < m || m < 0) return 0;
    return fac(n) * invfac(n - m);
  }
};

void solve() {
    int n, p;
    cin >> n >> p;
    m32::setMod(p);
    Comb<m32> comb;
    for(int i = 1; i <= n; ++i) {
        cout << comb.inv(i) << endl;
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}