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

using Z = ModInt<u32, 1'000'000'007>;

void Thephix() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> leaf;
    [&](this auto&& dfs, int u, int fa) -> void {
        int son = 0;
        for (auto v : adj[u]) {
            if (v == fa) continue;
            dfs(v, u);
            son++;
        }
        if (son == 0) leaf.push_back(u);
    } (1, 0);

    if (leaf.size() == 1) {
        cout << Z(2).pow(n) << "\n";
        return;
    }

    if (leaf.size() >= 3) {
        cout << 0 << "\n";
        return;
    }

    vector<int> deg(n + 1);
    for (int i = 1; i <= n; ++i) {
        deg[i] = adj[i].size();
    }
    int lca = max_element(deg.begin(), deg.end()) - deg.begin();

    vector<int> dep(n + 1);
    [&](this auto&& dfs, int u, int fa) -> void {
        dep[u] = dep[fa] + 1;
        for (auto v : adj[u]) {
            if (v == fa) continue;
            dfs(v, u);
        }
    } (1, 0);

    Z ans = Z(2).pow(dep[lca]);
    n -= dep[lca];

    int len0 = dep[leaf[0]] - dep[lca];
    int len1 = dep[leaf[1]] - dep[lca];

    Z res = 0;
    res += Z(2).pow(n - (min(len0, len1) * 2 + (len0 > len1)));
    res += Z(2).pow(n - (min(len0, len1) * 2 + (len1 > len0)));

    cout << ans * res << "\n";
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