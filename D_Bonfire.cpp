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
    int n, x, y, tx = 0, ty = 0;
    string s;
    cin >> n >> y >> x >> s;
    y = -y;
    set<array<int, 2>> S;
    S.insert({0, 0});
    for(auto op : s) {
        if(op == 'S') y++, ty++;
        if(op == 'N') y--, ty--;
        if(op == 'W') x++, tx++;
        if(op == 'E') x--, tx--;
        S.insert({tx, ty});
        if(S.contains({x, y})) {
            cout << '1';
        } else cout << '0';
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}