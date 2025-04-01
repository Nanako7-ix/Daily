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

array<i64, 10> f(i64 n) {
    array<int, 15> d {};
    for(int i = 0; ; ++i) {
        d[i] = n % 10;
        n /= 10;
        if(n == 0) break;
    }
    
    array<array<int, 10>, 15> ans {};
    for(int i = 0; i < 15; ++i) {
        for(int j = 0; j < d[i]; ++j) {
            ans[j] = 
        }
    }
}

void solve() {
    i64 a, b;
    cin >> a >> b;
    array<i64, 10> x = f(b), y = f(a - 1);
    for(int i = 0; i < 10; ++i) {
        cout << x[i] - y[i] << ' ';
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}