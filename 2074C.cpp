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
    int n;
    cin >> n;
    bitset<32> x(n);
    if(x.count() <= 1) {
        cout << "-1\n";
        return;
    }
    int p, cnt = 0;
    for(int i = 0; i < 32; ++i) {
        if(x[i] == 0) {
            x[i] = 1, p = i;
            break;
        } else cnt++;
    }
    for(int i = p + 1; i < 32; ++i) {
        if(x[i] == 1) {
            x[i] = 0; break;
        }
    }
    if(x.to_ullong() < n) {
        cout << x.to_ullong() << endl;
    } else {
        cout << "-1\n";
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}