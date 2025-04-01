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

void solve() {
    array<i64, 3> a;
    cin >> a[0] >> a[1] >> a[2];

    set<array<i64, 3>> S;
    for(auto x : a) for(auto y : a) for(auto z : a) {
        array<i64, 3> res {x, y, z};
        sort(res.begin(), res.end());
        if(res[0] + res[1] > res[2]) {
            S.insert(res);
        }
    }
    cout << S.size() << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}