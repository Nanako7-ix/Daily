#include<ext/pb_ds/assoc_container.hpp>
#include<bits/stdc++.h>
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
    string s;
    cin >> n >> s;
    ranges::reverse(s);
    set<int> S;
    for(int i = 0; i < n; ++i) {
        if(s[i] == '0') {
            S.insert(i);
        }
    }
    
    i64 ans = 0;
    for(int i = 0; i < n; ++i) {
        if(s[i] == 0) cout << 0;
        else {
            if(S.empty()) {
                cout << -1;
            } else {
                auto it = S.begin();
                cout << (ans += *it - i);
                S.erase(it);
            }
        }
        cout << " \n"[i == n - 1];
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}