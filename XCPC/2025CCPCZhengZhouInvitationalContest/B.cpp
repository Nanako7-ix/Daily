#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using u32 = unsigned;
using u64 = unsigned long long;

constexpr int Thephix = 0;
constexpr int N = 2000005;

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

using m32 = ModInt<u32, 998244353>;

void solve () {
    int n;
    cin >> n;

    int sum = 0;
    vector<int> cnt(n + 2);
    vector<vector<m32>> dp(n + 2);
    dp[0].push_back(1);
    for (int i = 1; i <= n; ++i) {
        int x; cin >> x;
        if (x == -1) {
            auto ndp = dp;
            m32 now = dp[0][0], inv = m32{1} / sum;
            ndp[0][0] = 0; // 注意清零
            for (int u = 1; u <= n + 1; ++u) {
                for (int x = 1; x <= cnt[u]; ++x) {
                    // 处理 dp[u][x]
                    ndp[u][x - 1] = (x == 1 ? now : dp[u][x - 2]) * (cnt[u] - x + 1) * inv;
                    now += dp[u][x - 1];
                }
            }
            swap(dp, ndp);
            sum--;
        } else {
            sum++;
            cnt[x + 1]++;
            dp[x + 1].push_back(0);
        }
    }

    m32 ans = 0;
    for (int u = 1; u <= n + 1; ++u) {
        for (int x = 1; x <= cnt[u]; ++x) {
            ans += dp[u][x - 1];
        }
    }
    cout << ans << "\n";
}

int main () {
    cin.tie(nullptr), cout.tie(nullptr);
    ios::sync_with_stdio(false);

    int T = 1;
    cin >> T;
    while (T--) {
        solve ();
    }

    return Thephix;
}