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
    i64 x, y;
    cin >> x >> y;
    
    function<int(int, int)> And = [](int x, int y) { return x & y; };
    function<int(int, int)> Or  = [](int x, int y) { return x | y; };
    function<int(int, int)> Xor = [](int x, int y) { return x ^ y; };
    function<int(int, int)> Gcd = [](int x, int y) { return gcd(x, y); };

    vector<i64> a {x, y};
    for(auto op : {And, Or, Xor, Gcd}) {
        if(op(x, y) == 0) {
            cout << 1 << endl;
            return;
        }
        a.push_back(op(x, y));
    }
    for(auto op : {And, Or, Xor, Gcd}) {
        for(int i = 0; i < 2; ++i) {
            for(int j = i + 1; j < (int) a.size(); ++j) {
                if(op(a[i], a[j]) == 0) {
                    cout << 2 << endl;
                    return;
                }
            }
        }
    }
    cout << 3 << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}