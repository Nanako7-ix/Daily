/**
 * Author:  Nanako7_ix
 * Created: 2025/05/03 03:00:56
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
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    s = ' ' + s;

    vector S(n + 1, vector<m32> (n + 1));
    auto A(S), B(S), BS(S), SB(S), BSB(S);

    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            if (j - i + 1 <= k) {
                S[i][j] = 1;
                for (int k = i; k <= j; ++k) {
                    if (s[k] == '(' || s[k] == ')') {
                        S[i][j] = 0;
                        break;
                    }
                }
            }
        }
    }

    for (int len = 2; len <= n; ++len) {
        for (int l = 1; l + len - 1 <= n; ++l) {
            int r = l + len - 1;

            // A: () (S) (SB) (BS) (B) (BSB)
            if (len == 2) {
                A[l][r] = (s[l] == '(' || s[l] == '?') && (s[r] == ')' || s[r] == '?');
            } else {
                if ((s[l] == '(' || s[l] == '?') && (s[r] == ')' || s[r] == '?')) {
                    A[l][r] +=  S[l + 1][r - 1];
                    A[l][r] +=  B[l + 1][r - 1];
                    A[l][r] += SB[l + 1][r - 1];
                    A[l][r] += BS[l + 1][r - 1];
                    A[l][r] += BSB[l + 1][r - 1];
                }
            }

            // B: AB A
            B[l][r] = A[l][r];
            for (int m = l; m < r; ++m) {
                B[l][r] += A[l][m] * B[m + 1][r];
            }

            // SB & BS
            for (int m = l; m < r; ++m) {
                SB[l][r] += S[l][m] * (B[m + 1][r] + BSB[m + 1][r]);
                BS[l][r] += (B[l][m] + BSB[l][m]) * S[m + 1][r];
            }

            // BSB: B + SB
            for (int m = l; m < r; ++m) {
                BSB[l][r] += B[l][m] * SB[m + 1][r];
            }
        }
    }

    cout << B[1][n] + BSB[1][n] << endl;
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
    
    int T = 1;
    // cin >> T;
    
    while (T--) {
        solve();
    }
    
    return 0;
}