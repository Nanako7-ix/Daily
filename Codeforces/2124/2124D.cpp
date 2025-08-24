/**
 *
 *  $$$$$$\  $$$$$$\  $$$$$$\  $$\       $$\       $$$$$$\  
 * $$  __$$\ \_$$  _|$$  __$$\ $$ |      $$ |     $$  __$$\ 
 * $$ /  \__|  $$ |  $$ /  $$ |$$ |      $$ |     $$ /  $$ |
 * $$ |        $$ |  $$$$$$$$ |$$ |      $$ |     $$ |  $$ |
 * $$ |        $$ |  $$  __$$ |$$ |      $$ |     $$ |  $$ |
 * $$ |  $$\   $$ |  $$ |  $$ |$$ |      $$ |     $$ |  $$ |
 *  $$$$$$ | $$$$$$\ $$ |  $$ |$$$$$$$$\ $$$$$$$$\ $$$$$$  |
 * \______/  \______|\__|  \__|\________|\________|\______/ 
 *
 * Author:  Nanako7_ix
 * Created: 2025/07/06 23:20:28
 * 好想和 めぐる 一起打 xcpc 啊
 */
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define debug(x) cerr << "\033[31m" << #x << " = " << x << "\033[0m\n"
using namespace std;
using namespace __gnu_pbds;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64 = double;

constexpr int inf = 0x3f3f3f3f;
constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    if (k == 1) {
        cout << "YES\n";
    } else {
        auto b = a;
        sort(b.begin() + 1, b.end());

        vector<int> p;
        for (int i = 1; i <= n; ++i) {
            if (a[i] < b[k]) {
                p.push_back(i);
            }
        }

        if (p.size() == 0) {
            cout << "YES\n";
            return;
        }

        vector<int> cnt(n + 1);
        for (int i = 1; i <= n; ++i) {
            cnt[i] = cnt[i - 1] + (a[i] == b[k]);
        }
        
        int need = k - 1 - p.size(), m = p.size();
        for (int i = 0, j = m - 1; i <= j; ++i, --j) {
            if (a[p[i]] != a[p[j]]) {
                cout << "NO\n";
                return;
            }

            need -= 2 * min(
                cnt[p[i]] - cnt[i == 0 ? 0 : p[i - 1]],
                cnt[j == m - 1 ? n : p[j + 1]] - cnt[p[j]]
            );

            if (i + 1 == j) {
                need -= cnt[p[j]] - cnt[p[i]];
            }

        }
        
        if (need <= 0) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
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