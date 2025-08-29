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

using Z = ModInt<u32, 998244353>;

struct AhoCorasick {
    static constexpr int N = 26;
    struct Node {
        int len, fail;
        std::vector<int> adj;
        std::array<int, N> next;
        Node() : len(0), fail(0), adj{}, next{} {}
    };

    std::vector<Node> t;
    
    AhoCorasick(int n = 0) {
        t.reserve(n);
        t.assign(2, Node());
        t[0].next.fill(1);
        t[0].len = -1;
        t[0].adj.push_back(1);
    }
    
    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }
    
    int insert(const std::string& s) {
        int p = 1;
        for (auto c : s) {
            int x = c - 'a';
            if (t[p].next[x] == 0) {
                t[p].next[x] = newNode();
                t[t[p].next[x]].len = t[p].len + 1;
            }
            p = t[p].next[x];
        }
        return p;
    }
    
    void work() {
        std::queue<int> q;
        q.push(1);
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for (int i = 0; i < N; i++) {
                if (t[u].next[i] == 0) {
                    t[u].next[i] = t[t[u].fail].next[i];
                } else {
                    t[t[u].next[i]].fail = t[t[u].fail].next[i];
                    t[t[t[u].fail].next[i]].adj.push_back(t[u].next[i]);
                    q.push(t[u].next[i]);
                }
            }
        }
    }
    
    int len(int p) {
        return t[p].len;
    }
    
    int fail(int p) {
        return t[p].fail;
    }
    
    const std::vector<int>& adj(int p) {
        return t[p].adj;
    }
    
    int next(int p, int x) {
        return t[p].next[x];
    }
    
    int size() {
        return t.size();
    }
};

void Thephix() {
    int n, l;
    cin >> n >> l;

    AhoCorasick ac(10 * n);
    vector<int> jxt(10 * n);
    for (int i = 1; i <= n; ++i) {
        string s;
        cin >> s;
        jxt[ac.insert(s)] |= 1 << (i - 1);
    }
    ac.work();

    int tot = ac.size() - 1;
    auto dfs = [&](auto&& dfs, int u) -> void {
        for (auto v : ac.adj(u)) {
            jxt[v] |= jxt[u];
            dfs(dfs, v);
        }
    };
    dfs(dfs, 1);

    vector dp(1 << n , vector<Z> (tot + 1));
    dp[0][1] = 1;
    for (int i = 1; i <= l; ++i) {
        vector ndp(1 << n , vector<Z> (tot + 1));
        for (int s = 0; s < (1 << n); ++s) {
            for (int u = 1; u <= tot; ++u) {
                for (int ch = 0; ch < 26; ++ch) {
                    int v = ac.next(u, ch);
                    ndp[s | jxt[v]][v] += dp[s][u];
                }
            }
        }
        swap(dp, ndp);
    }
    cout << accumulate(dp[(1 << n) - 1].begin(), dp[(1 << n) - 1].end(), Z(0)) << "\n";;
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