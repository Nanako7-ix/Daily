#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

template<typename Info>
struct ChthollyTree {
    struct Node {
        i64 l, r;
        mutable Info v;
        Node (i64 l, i64 r, Info v) {
            this -> l = l;
            this -> r = r;
            this -> v = v;
        }
        bool operator< (const Node& o) const {
            return l < o.l;
        }
    };

    int n;
    set<Node> odt;
    ChthollyTree () = default;

    ChthollyTree (int n, Info v = {}) {
        init(n, v);
    }

    void init (int n, Info v = {}) {
        this -> n = n;
        odt.clear();
        odt.emplace(1, n, v);
    }

    set<Node>::iterator split(int p) {
        if (p == n + 1) return odt.end();
        auto it = odt.lower_bound(Node {p, 0, 0});
        if (it != odt.end() && it->l == p) return it;
        --it;
        auto [l, r, v] = *it;
        odt.erase(it);
        odt.emplace(l, p - 1, v);
        return odt.emplace(p, r, v).first;
    }

    void assign (int l, int r, Info v) {
        auto itr = split(r + 1);
        auto itl = split(l);
        odt.erase(itl, itr);
        odt.emplace(l, r, v);
    }

    template<typename Func>
    void perform(int l, int r, Func&& opt) {
        auto itr = split(r + 1);
        auto itl = split(l);
        for (auto it = itl; it != itr; ++it) {
            auto [l, r, v] = *it;
            opt(l, r, v);
        }
    }
};

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
    constexpr ModInt pow(i64 b) const {
        ModInt res = 1, a = *this;
        b = (b % (Mod - 1) + Mod - 1) % (Mod - 1);
        for (; b; b >>= 1, a *= a) {
            if (b & 1) res *= a;
        }
        return res;
    }
private:
    U x;
};

using Z = ModInt<u32, 998244353>;

void Thephix() {
    int n, q;
    cin >> n >> q;
    ChthollyTree<Z> odt(n);
    for (int i = 1; i <= n; ++i) {
        int x; cin >> x;
        odt.assign(i, i, x);
    }
    while (q--) {
        int l, r;
        cin >> l >> r;
        Z sum = 0;
        odt.perform(l, r, [&](int l, int r, const Z& info) {
            sum += info * (r - l + 1);
        });
        odt.assign(l, r, sum / (r - l + 1));
    }
    for (auto [l, r, val] : odt.odt) {
        for (int i = l; i <= r; ++i) {
            cout << val << " \n"[i == n];
        }
    }
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