// Author: Nanako7_ix
// Created: 2025/03/29 23:18:22
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
    string s;
    cin >> n >> s;
    vector<int> a(n + 1);
    array<int, 3> cnt {};
    for(int i = 1; i <= n; ++i) {
        if(s[i - 1] == 'L') a[i] = 0;
        if(s[i - 1] == 'I') a[i] = 1;
        if(s[i - 1] == 'T') a[i] = 2;
        cnt[a[i]]++;
    }

    if(!cnt[0] + !cnt[1] + !cnt[2] == 2) {
        cout << "-1\n";
        return;
    }

    cout << 2 * n << endl;
    for(int i = 1; i <= n; ++i) {
        if(a[i] != a[i + 1]) {
            for(int j = 1; j <= cnt[a[i]]; ++j) {
                cout << i << endl;
                cout << i << endl;
            }
            for(int j = 1; j <= cnt[a[i + 1]]; ++j) {
                cout << i + 1 << endl;
                cout << i + 1 << endl;
            }
            for(int j = 1; j <= cnt[3 ^ a[i] ^ a[i + 1]]; ++j) {
                cout << i + 2 << endl;
                cout << i + 2 << endl;
            }
            break;
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