/**
 * Author: Nanako7_ix
 * Created: 2025/04/14 00:19:45
 */
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
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
    string s, t;
    cin >> s >> t;
    queue<int> S, T;
    for(auto x : s) {
        if(x == 'L') {
            S.push(0);
        } else S.push(1);
    }
    for(auto x : t) {
        if(x == 'L') {
            T.push(0);
        } else T.push(1);
    }

    while(!S.empty()) {
        int now = S.front();
        int cnt1 = 0, cnt2 = 0;
        while(!S.empty() && S.front() == now) {
            cnt1++, S.pop();
        }
        while(!T.empty() && T.front() == now) {
            cnt2++, T.pop();
        }
        if(cnt1 <= cnt2 && cnt2 <= 2 * cnt1) {
            continue;
        }
        cout << "NO\n";
        return;
    }
    if (!T.empty()) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
    }
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
    
    int T = 1;
    cin >> T;
    
    while (T--) {
        solve();
    }
    
    return 0;
}