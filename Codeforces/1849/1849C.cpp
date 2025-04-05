// Author: Nanako7_ix
// Created: 2025/04/04 23:02:19
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

struct Hashing {    
    using m32 = DynModInt<416>;
    static int n;
    static int Mod;
    static array<vector<m32>, 2> f;
    constexpr static array<i64, 2> base { 131,13331 };

    static void init (int m) {
        if(m <= n) return;
        f[0].resize(2 * m), f[1].resize(2 * m);

        for (int i = n; i < 2 * m; ++i) {
            f[0][i] = f[0][i - 1] * base[0];
            f[1][i] = f[1][i - 1] * base[1];
        }
        n = 2 * m;
    }

    static bool isPrime (int n) {
        if (n <= 2) return false;
        for (i64 i = 2; i * i <= n; ++i) {
            if (n % i == 0) return false;
        }
        return true;
    }

    static int findPrime (int n) {
        while (!isPrime(n)) n++;
        return n;
    }

    static int findPrime () {
        mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
        m32::setMod(findPrime(rng() % 900000000 + 100000000));
        return m32::Mod();
    }

    static m32 p (int i, int n) {
        init(n + 1);
        return f[i][n];
    }

    array<vector<m32>, 2> h;

    Hashing () = default;

    Hashing (const string& s) {
        init(s);
    }

    void init (const string& s) {
        int n = s.size();
        h[0].assign(n + 1, 0);
        h[1].assign(n + 1, 0);
        
        for (int i = 1; i <= n; ++i) {
            h[0][i] = h[0][i - 1] * base[0] + s[i - 1];
            h[1][i] = h[1][i - 1] * base[1] + s[i - 1];
        }
    }

    array<m32, 2> query (int l, int r) {
        l--;
        assert(l < r);
        return {
            h[0][r] - h[0][l] * p(0, r - l),
            h[1][r] - h[1][l] * p(1, r - l)
        };
    }
};

int Hashing::n = 1;
int Hashing::Mod = Hashing::findPrime();

array<vector<Hashing::m32>, 2> Hashing::f {
    vector<Hashing::m32> {1},
    vector<Hashing::m32> {1}
};

void solve() {
    int n, m;
    string s;
    cin >> n >> m >> s;
    Hashing hs(s);
    set<array<Hashing::m32, 2>> S;

    vector<int> pre(n + 1);
    for(int i = 1; i <= n; ++i) {
        pre[i] = (s[i - 1] == '1') + (i == 0 ? 0 : pre[i - 1]);
    }

    vector<array<Hashing::m32, 2>> f(n);
    for(int i = 0; i < n; ++i) {
        f[i][0] = Hashing::p(0, i) + (i == 0 ? 0 : f[i - 1][0]);
        f[i][1] = Hashing::p(1, i) + (i == 0 ? 0 : f[i - 1][1]);
    }

    auto val = hs.query(1, n);
    for(int i = 1; i <= m; ++i) {
        int l, r;
        cin >> l >> r;
        int c = pre[r] - pre[l - 1];
        if(c == r - l + 1 || c == 0) {
            S.insert(val);
            continue;
        }
        array<Hashing::m32, 2> delt {0, 0};
        delt[0] = '0' * (f[r - l][0] - f[c - 1][0]) + '1' * f[c - 1][0];
        delt[1] = '0' * (f[r - l][1] - f[c - 1][1]) + '1' * f[c - 1][1];

        auto get = hs.query(l, r);
        S.insert({
            val[0] + (delt[0] - get[0]) * Hashing::p(0, n - r),
            val[1] + (delt[1] - get[1]) * Hashing::p(1, n - r)
        });
    }
    cout << S.size() << endl;
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