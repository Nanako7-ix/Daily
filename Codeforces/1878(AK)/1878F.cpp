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
constexpr int N = 1000000;

vector<int> minp, primes;
void sieve(int N) {
    minp.assign(N + 1, 0);
    primes.clear();
    for(int i = 2; i <= N; ++i) {
        if(!minp[i]) primes.emplace_back(minp[i] = i);
        for(auto p : primes) {
            if(i * p > N) break;
            minp[i * p] = p;
            if(i % p == 0) break;
        }
    }
}

void solve() {
    int _n, q;
    cin >> _n >> q;
    
    i64 n = _n;
    map<int, int> a;
    while(_n != 1) {
        a[minp[_n]]++;
        _n /= minp[_n];
    }
    auto b = a;

    auto check = [&]() {
        int ans = 1;
        for(auto [_, c] : b) {
            ans *= c + 1;
        }
        return ans;
    };
    vector<int> X;
    while(q--) {
        int op; cin >> op;
        if(op == 1) {
            i64 x; cin >> x;
            X.push_back(x);
            while(x != 1) {
                b[minp[x]]++;
                x /= minp[x];
            }
            int d = check();
            i64 sum = n % d;
            for(auto x : X) {
                sum = sum * x % d;
            }
            if(sum == 0) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        } else {
            b = a;
            X.clear();
        }
    }
    cout << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    sieve(N);
    cin >> T;
    while(T--) solve();
    return 0;
}