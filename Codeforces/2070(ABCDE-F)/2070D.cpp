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

template<int Mod>
struct ModInt {
public:
  constexpr ModInt() : x(0) {}
  constexpr ModInt(auto x) : x((x % Mod + Mod) % Mod) {}
  constexpr u64 val() const { return x; }
  constexpr static int mod() { return Mod; }
  constexpr ModInt operator-() const { return x == 0 ? 0 : Mod - x; }
  constexpr ModInt inv() const { return power(*this, Mod - 2); }
  constexpr ModInt& operator+=(const ModInt& rhs) & { x += rhs.val(); if(x >= Mod) x -= Mod; return *this; }
  constexpr ModInt& operator-=(const ModInt& rhs) & { x -= rhs.val(); if(x >= Mod) x += Mod; return *this; }
  constexpr ModInt& operator*=(const ModInt& rhs) & { (x *= rhs.val()) %= Mod; return *this; }
  constexpr ModInt& operator/=(const ModInt& rhs) & { return *this *= rhs.inv(); }
  friend constexpr ModInt operator+(ModInt lhs, const ModInt& rhs) { return lhs += rhs; }
  friend constexpr ModInt operator-(ModInt lhs, const ModInt& rhs) { return lhs -= rhs; }
  friend constexpr ModInt operator*(ModInt lhs, const ModInt& rhs) { return lhs *= rhs; }
  friend constexpr ModInt operator/(ModInt lhs, const ModInt& rhs) { return lhs /= rhs; }
  friend constexpr strong_ordering operator<=>(const ModInt &lhs, const ModInt &rhs) = default;
  friend istream& operator>>(istream& is, ModInt& a) { i64 x; is >> x; a = ModInt(x); return is; }
  friend ostream& operator<<(ostream& os, const ModInt& a) { os << a.val(); return os; }
private:
  u64 x;
};

using m32 = ModInt<998244353>;

m32 solve() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    for(int i = 2; i <= n; ++i) {
        int p; cin >> p;
        adj[p].push_back(i);
    }

    vector<int> dep(n + 1);
    vector<vector<int>> a(n + 1);
    [&](this auto&& dfs, int u) -> void {
        for(auto v : adj[u]) {
            dep[v] = dep[u] + 1;
            dfs(v);
        }
        a[dep[u]].push_back(u);
    } (1);
    
    vector<m32> dp(n + 1), sum(n + 1);
    for(int i = n; i >= 0; --i) {
        for(auto u : a[i]) {
            dp[u] = sum[i + 1];
            if(u != 1) for(auto v : adj[u]) {
                dp[u] -= dp[v];
            }
            dp[u] += 1;
            sum[i] += dp[u];
        }
    }

    return dp[1];
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) cout << solve() << endl;
    return 0;
}