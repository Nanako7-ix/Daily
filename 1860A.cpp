/**
 * Author: Nanako7_ix
 * Created: 2025/04/24 01:07:43
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
    cin >> s;

    if (s == "()") {
        cout << "NO\n";
        return;
    }

    int n = s.size();

    auto lrlr = [&]() {
        cout << "YES\n";
        for (int i = 1; i <= 2 * n; ++i) {
            if (i & 1) {
                cout << '(';
            } else {
                cout << ')';
            }
        }
        cout << endl;
    };

    auto llrr = [&]() {
        cout << "YES\n";
        for (int i = 1; i <= n; ++i) {
            cout << '(';
        }
        for (int i = 1; i <= n; ++i) {
            cout << ')';
        }
        cout << endl;
    };

    int same = 0;
    for (int i = 1; i < n; ++i) {
        if (s[i] == s[i - 1]) {
            lrlr();
            return;
        }
    }

    llrr();
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