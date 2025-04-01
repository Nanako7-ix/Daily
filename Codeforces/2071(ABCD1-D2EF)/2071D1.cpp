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

int solve() {
    i64 n, l, r;
    cin >> n >> l >> r;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
        a[i] ^= a[i - 1];
    }

    if(n % 2 == 0) {
        a.push_back(a[++n / 2]);
        a[n] ^= a[n - 1];
    }

    if(l <= n) return a[l] ^ a[l - 1];
    
    return [&](this auto&&f, i64 p) -> int {
        if(p <= n) return a[p];
        if(p & 1) return a[n];
        return f(p >> 1) ^ a[n];
    } (l >> 1);
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) cout << solve() << endl;
    return 0;
}