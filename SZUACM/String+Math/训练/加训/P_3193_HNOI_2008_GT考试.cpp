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
 * Created: 2025/05/20 22:33:46
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

using m32 = DynModInt<0>;

struct KMP : string {
    vector<int> nxt;
    KMP(string s) : string(s), nxt(size()) {
        int n = s.size();
        for(int i = 1, j = 0; i < n; ++i) {
            while(j && at(i) != at(j)) j = nxt[j - 1];
            nxt[i] = j += (at(i) == at(j));
        }
    }
    vector<int> work(string s) {
        int n = s.size();
        vector<int> res;
        for(int i = 0, j = 0; i < n; ++i) {
            while(j && s[i] != at(j)) j = nxt[j - 1];
            j += (s[i] == at(j));
            if(j == (int) size()) res.push_back(i - j + 1), j = nxt[j - 1];
        }
        return res;
    }
};

vector<vector<m32>> mul(const vector<vector<m32>>& x, const vector<vector<m32>>& y) {
    int n = x.size();
    vector ans(n, vector<m32> (n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                ans[i][j] += x[i][k] * y[k][j];
            }
        }
    }
    return ans;
}

vector<vector<m32>> power(vector<vector<m32>> a, i64 b) {
    int n = a.size();
    vector res(n, vector<m32> (n));
    for (int i = 0; i < n; ++i) {
        res[i][i] = 1;
    }
    for (; b; b >>= 1, a = mul(a, a)) {
        if (b & 1) res = mul(res, a);
    }
    return res;
}

template<typename T, int N>
struct Matrix {
    array<array<T, N>, N> a;
    Matrix E (const T& e = {1}, const T& o = {0}) {
        Matrix mat = O(o);
        for (int i = 0; i < N; ++i) {
            mat[i][i] = e;
        }
        return mat;
    }
    Matrix O (const T& o = {0}) {
        Matrix mat;
        for (int i = 0; i < N; ++i) {
            fill(mat[i].begin(), mat[i].end(), o);
        }
        return mat;
    }
    Matrix operator- () const {
        Matrix mat(a);
        for (int i = 0; i < N; ++i) {}
    }
    friend 
};

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    m32::setMod(k);

    string s;
    cin >> s;
    KMP kmp(s);
    auto nxt = kmp.nxt;

    vector<vector<m32>> mat(m + 1, vector<m32> (m + 1));
    for (int i = 0; i < m; ++i) {
        for (int j = '0'; j <= '9'; ++j) {
            int len = i;
            while (len != 0 && j != s[len]) {
                len = nxt[len - 1];
            }
            len += j == s[len];
            mat[i][len] += 1;
        }
    }
    mat[m][m] = 10;
    mat = power(mat, n);

    m32 ans = 0;
    for (int i = 0; i < m; ++i) {
        ans += mat[0][i];
    }
    cout << ans << endl;
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