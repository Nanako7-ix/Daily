/**
 * Author: Nanako7_ix
 * Created: 2025/04/12 17:01:48
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
    string s;
    i64 P;
    cin >> s >> P;
    int n = s.size();
    s = ' ' + s;

    int cnt = 0;
    while(P > n - cnt) {
        P -= n - cnt;
        cnt++;
    }

    set<int> S, alive;
    for(int i = 1; i <= n; ++i) {
        alive.insert(i);
    }
    vector<int> nxt(n + 1, -1);
    for(int i = 1; i < n; ++i) {
        nxt[i] = i + 1;
        if(s[i] > s[nxt[i]]) {
            S.insert(i);
        }
    }

    auto erase = [&]() -> void {
        if(S.empty()) {
            int p = *alive.rbegin();
            alive.erase(p);
        } else {
            // 删 p
            int p = *S.begin();
            // p 似了
            alive.erase(p);
            S.erase(p);
            // 看看 p 在字符串中在哪
            auto it = alive.lower_bound(p);
            // 如果是字符串头, 就无法更新
            // 否则, 前面那个字符的 nxt 就变成了 p 的 nxt
            if(it != alive.begin()) {
                int lft = *prev(it);
                nxt[lft] = nxt[p];
                if(s[lft] > s[nxt[lft]]) {
                    S.insert(lft);
                }
            }
        }
    };
    for(int i = 1; i <= cnt; ++i) {
        erase();
    }
    for(int i = 1; i < P; ++i) {
        alive.erase(alive.begin());
    }
    cout << s[*alive.begin()];
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
    
    int T = 1;
    cin >> T;
    
    while (T--) {
        solve();
    }

    cout << endl;
    
    return 0;
}