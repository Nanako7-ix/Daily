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

struct Hashing {
    static int n;
    static array<vector<int>, 2> f;
    static array<int, 2> Mod;
    constexpr static array<i64, 2> base {131, 13331};
    static void init (int m) {
        if(m <= n) return;
        f[0].resize(2 * m), f[1].resize(2 * m);
        for(int i = n; i < 2 * m; ++i) {
            f[0][i] = f[0][i - 1] * base[0] % Mod[0];
            f[1][i] = f[1][i - 1] * base[1] % Mod[1];
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
    static i64 p (int i, int n) {
        init(n + 1);
        return f[i][n];
    }

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
        return {
            (h[0][r] - h[0][l - 1] * p(0, r - l + 1) % Mod[0] + Mod[0]) % Mod[0],
            (h[1][r] - h[1][l - 1] * p(1, r - l + 1) % Mod[1] + Mod[1]) % Mod[1]
        };
    }
};

array<int, 2> Hashing::Mod = Hashing::findPrime();
array<vector<int>, 2> Hashing::f {vector<int> {1}, vector<int> {1}};
int Hashing::n = 1;

void solve() {
    int n, m;
    string s;
    cin >> n >> m >> s;
    Hashing hs(s);
    set<array<i64, 2>> S;

    vector<int> pre(n);
    for(int i = 0; i < n; ++i) {
        pre[i] = (s[i] == '1') + (i == 0 ? 0 : pre[i - 1]);
    }

    vector<array<i64, 2>> f(n);
    for(int i = 0; i < n; ++i) {
        f[i][0] = Hashing::p(0, i) + (i == 0 ? 0 : f[i - 1][0]);
        f[i][1] = Hashing::p(1, i) + (i == 0 ? 0 : f[i - 1][1]);
        f[i][0] %= Hashing::Mod[0], f[i][1] %= Hashing::Mod[1];
    }

    auto val = hs.query(0, n - 1);
    for(int i = 1; i <= m; ++i) {
        int l, r;
        cin >> l >> r;
        int c = pre[r - 1] - (l == 1 ? 0 : pre[l - 2]);
        if(c == r - l + 1 || c == 0) {
            S.insert(val);
            continue;
        }
        array<i64, 2> delt {0, 0};
        delt[0] = ((48 * (f[r - l][0] - f[c - 1][0])) % Hashing::Mod[0]
                + (49 * f[c - 1][0]) % Hashing::Mod[0]) % Hashing::Mod[0];
        delt[1] = ((48 * (f[r - l][1] - f[c - 1][1])) % Hashing::Mod[1]
                + (49 * f[c - 1][1]) % Hashing::Mod[1]) % Hashing::Mod[1];

        auto get = hs.query(l - 1, r - 1);

        delt[0] = ((delt[0] - get[0]) % Hashing::Mod[0] + Hashing::Mod[0]) % Hashing::Mod[0];
        delt[1] = ((delt[1] - get[1]) % Hashing::Mod[1] + Hashing::Mod[1]) % Hashing::Mod[1];
        (delt[0] *= Hashing::p(0, n - r)) %= Hashing::Mod[0];
        (delt[1] *= Hashing::p(1, n - r)) %= Hashing::Mod[1];
        S.insert({
            (val[0] + delt[0]) % Hashing::Mod[0],
            (val[1] + delt[1]) % Hashing::Mod[1]
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