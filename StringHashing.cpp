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

struct Hashing {
private:
    static int n;
    static array<vector<int>, 2> p;
    static array<int, 2> Mod;
    constexpr static array<i64, 2> base {131, 13331};
    static void init (int m) {
        if(m <= n) return;
        p[0].resize(2 * m), p[1].resize(2 * m);
        for(int i = n; i < 2 * m; ++i) {
            p[0][i] = p[0][i - 1] * base[0] % Mod[0];
            p[1][i] = p[1][i - 1] * base[1] % Mod[1];
        }
        n = 2 * m;
    }
    static bool isPrime (int n) {
        if(n <= 2) return false;
        for(i64 i = 2; i * i <= n; ++i) {
            if(n % i == 0) return false;
        }
        return true;
    }
    static int findPrime (int n) {
        while(!isPrime(n)) n++;
        return n;
    }
    static array<int, 2> findPrime () {
        mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
        return {
            findPrime(rng() % 900000000 + 100000000),
            findPrime(rng() % 900000000 + 100000000)
        };
    }
    array<vector<i64>, 2> h;
public:
    Hashing () = default;
    Hashing (const string& s) {
        init(s);
    }
    void init (const string& s) {
        int n = s.size();
        h[0].assign(n, 0);
        h[1].assign(n, 0);
        
        h[0][0] = h[1][0] = s[0];
        for(int i = 1; i < n; ++i) {
            h[0][i] = (h[0][i - 1] * base[0] + s[i]) % Mod[0];
            h[1][i] = (h[1][i - 1] * base[1] + s[i]) % Mod[1];
        }
    }
    array<i64, 2> query (int l, int r) {
        assert(l <= r);
        if(l == 0) return {h[0][r], h[1][r]};
        init(r - l + 1);
        return {
            (h[0][r] - h[0][l - 1] * p[0][r - l] % Mod[0] + Mod[0]) % Mod[0],
            (h[1][r] - h[1][l - 1] * p[1][r - l] % Mod[1] + Mod[1]) % Mod[1]
        };
    }
};

array<int, 2> Hashing::Mod = Hashing::findPrime();
array<vector<int>, 2> Hashing::p {vector<int> {131}, vector<int> {13331}};
int Hashing::n = 1;

void solve() {
    
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}