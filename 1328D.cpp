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
    vector<int> a(n + 1);
    set<int> S;
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
        S.insert(a[i]);
    }
    if(S.size() == 1) {
        cout << 1 << endl;
        for(int i = 1; i <= n; ++i) {
            cout << 1 << " \n"[i == n];
        }
    } else if(S.size() == 2) {
        cout << 2 << endl;
        for(int i = 1; i <= n; ++i) {
            cout << 1 + (a[i] == a[1]) << " \n"[i == n];
        }
    } else {
        a[0] = a[n];
        int p = -1;
        for(int i = 1; i <= n; ++i) {
            if(a[i] == a[i - 1]) {
                p = i;
                break;
            }
        }
        if(p == -1) {
            if(n % 2 ==)
        } else {
            cout << 2 << endl;
            
        }
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}