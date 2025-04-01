// Author: Nanako7_ix
// Created: 2025/03/24 21:09:52
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
    string s;
    cin >> s;

    int n = s.size();
    vector<int> a(n + 1), nxt(n + 1, n + 1), stk {0};
    for(int i = 1; i <= n; ++i) {
        a[i] = a[i - 1] + (s[i - 1] == '(' ? 1 : -1);
        while(!stk.empty() && a[i] < a[stk.back()]) {
            nxt[stk.back()] = i;
            stk.pop_back();
        }
        stk.push_back(i);
    }

    // for(int i = 0; i <= n; ++i) {
    //     cerr << nxt[i] << " \n"[i == n];
    // }

    map<int, int> cnt;
    for(int i = 1; i <= n; ++i) {
        if(s[i - 1] == ')') continue;
        cout << i << ' ' << nxt[i - 1] - 1 << endl;
        if(a[nxt[i - 1] - 1] == a[i - 1]) {
            cnt[nxt[i - 1] - i]++;
        }
    }

    if(!cnt.empty()) {
        cout << cnt.rbegin() -> first << ' ' << cnt.rbegin() -> second << endl;
    } else cout << "0 1\n";
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}