/**
 * Author:  Nanako7_ix
 * Created: 2025/04/28 22:53:31
 * 好想和 めぐる 一起打 xcpc 啊
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

char solve() {
    int n;
    string s;
    cin >> n >> s;
    if (n == 2) {
        return s[0];
    }
    if (n == 3) {
        int A = 0, B = 0;
        for (auto x : s) {
            if (x == 'A') A++;
            if (x == 'B') B++;
        }
        if (A > 1) return 'A';
        if (B > 1) return 'B';
    }
    if (s[0] == s[n - 1]) {
        return s[0];
    }
    if (s[n - 2] == s[n - 1]) {
        return s[n - 1];
    }

    int ok = 0;
    char x = s[n - 1];
    for (int i = 0; i < n - 1; ++i) {
        ok |= s[i] == x;
    }

    if (x == 'B' && ok == 0) {
        return 'A';
    } else return 'B';
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
    
    int T = 1;
    cin >> T;
    
    while (T--) {
        cout << (solve() == 'A' ? "Alice\n" : "Bob\n");
    }
    
    return 0;
}