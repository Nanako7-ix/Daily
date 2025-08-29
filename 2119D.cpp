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
 * Created: 2025/07/06 00:12:54
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

constexpr i64 exgcd(i64 a, i64 b, i64& x, i64& y) {
    if(b == 0) {
        assert(a != 0);
        x = a / std::abs(a), y = 0;
        return std::abs(a);
    }
    i64 d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
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

    template<std::unsigned_integral T>
    constexpr DynModInt(T v) : x(v % Mod()) {}

    template<std::signed_integral T>
    constexpr DynModInt(T v) {
        int t = v % int(Mod());
        if(t < 0) {
            t += Mod();
        }
        x = t;
    }

    constexpr static void setMod(u32 m) {
        bt = m;
    }

    constexpr static u32 Mod() {
        return bt.Mod();
    }

    constexpr u32 val() const {
        return x;
    }

    constexpr DynModInt operator-() const {
        return x == 0 ? 0 : Mod() - x;
    }

    constexpr DynModInt inv() const {
        i64 x, y;
        assert(exgcd(this -> x, Mod(), x, y) == 1);
        return x;
    }

    constexpr DynModInt& operator+=(const DynModInt& rhs) & {
        x += rhs.val();
        if(x >= Mod()) {
            x -= Mod();
        }
        return *this;
    }

    constexpr DynModInt& operator-=(const DynModInt& rhs) & {
        x -= rhs.val();
        if(x >= Mod()) {
            x += Mod();
        }
        return *this;
    }

    constexpr DynModInt& operator*=(const DynModInt& rhs) & {
        x = bt.mul(x, rhs.val());
        return *this;
    }

    constexpr DynModInt& operator/=(const DynModInt& rhs) & {
        return *this *= rhs.inv();
    }

    friend constexpr DynModInt operator+(DynModInt lhs, const DynModInt& rhs) {
        return lhs += rhs;
    }

    friend constexpr DynModInt operator-(DynModInt lhs, const DynModInt& rhs) {
        return lhs -= rhs;
    }

    friend constexpr DynModInt operator*(DynModInt lhs, const DynModInt& rhs) {
        return lhs *= rhs;
    }

    friend constexpr DynModInt operator/(DynModInt lhs, const DynModInt& rhs) {
        return lhs /= rhs;
    }

    friend constexpr std::strong_ordering operator<=> (const DynModInt &lhs, const DynModInt &rhs) = default;

    friend std::istream& operator>>(std::istream& is, DynModInt& a) {
        i64 x;
        is >> x;
        a = DynModInt {x};
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const DynModInt& a) { 
        os << a.val();
        return os;
    }
private:
    u32 x;
    static Barrett bt;
};

template<u32 Id> Barrett DynModInt<Id>::bt = 998244353;

using m32 = DynModInt<114514>;

void solve() {
    int n, m;
    cin >> n >> m;
    m32::setMod(m);
    // 构造序列 -- 答案序列
    // dp 讨论答案序列

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