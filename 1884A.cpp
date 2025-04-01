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

void presolve() {
    
}

bool check(i64 x, int k) {
    int sum = 0;
    while(x) {
        sum += x % 10;
        x /= 10;
    }
    return sum % k == 0;
}

void solve() {
    int x, k;
    cin >> x >> k;
    while(!check(x, k)) x++;
    cout << x << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    presolve();
    while(T--) solve();
    return 0;
}