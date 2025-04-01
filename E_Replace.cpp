// Author: Nanako7_ix
// Created: 2025/03/29 22:11:39
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
    string s, t;
    array<int, 26> nxt {};
    fill(nxt.begin(), nxt.end(), -1);
    cin >> n >> s >> t;
    for(int i = 0; i < n; ++i) {
        if(nxt[s[i] - 'a'] != -1 && nxt[s[i] - 'a'] != t[i] - 'a') {
            cout << "-1\n";
            return;
        }
        nxt[s[i] - 'a'] = t[i] - 'a';
    }

    int ans = 0;
    array<int, 26> vis {};
    for(int i = 0; i < 26; ++i) {
        if(vis[i] || nxt[i] == -1 || nxt[i] == i) continue;
        cout << i << endl;
        for(int j = i; nxt[j] != -1; j = nxt[j]) {
            cout << j << ' ';
            if(j == i && vis[j]) {
                cout << "circle" << i << endl;
                ans++;
                break;
            }
            ans++;
            vis[j] = 1;
        }
        cout << endl;
    }
    cout << ans << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}