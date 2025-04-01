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
    int n, q;
    cin >> n >> q;
    vector<int> p(n + 1), a(n + 1), mp(n + 1);
    iota(p.begin(), p.end(), 0);
    iota(a.begin(), a.end(), 0);
    iota(mp.begin(), mp.end(), 0);

    while(q--) {
        int op; cin >> op;
        if(op == 1) {
            int x, y; cin >> x >> y;
            p[x] = mp[y];
        } else if(op == 2) {
            int x, y; cin >> x >> y;
            swap(a[mp[x]], a[mp[y]]);
            swap(mp[x], mp[y]);
        } else {
            int x; cin >> x;
            cout << a[p[x]] << endl;
        }   
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}