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
 * Created: 2025/06/07 21:42:54
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
using f64 = double;

constexpr int inf = 0x3f3f3f3f;
constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), deg(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        deg[a[i]]++;
    }

    vector<int> dp(n + 1), col(n + 1);
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (deg[i] == 0) q.push(i);
    }
    while (!q.empty()) {
        int u = q.front(), v = a[u];
        q.pop();
        col[u] = dp[u] != 0;
        dp[v] += col[u] == 0;
        if (--deg[v] == 0) {
            q.push(v);
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (deg[i] == 0) continue;
        int f = -1;
        vector<int> loop;
        for (int u = i; deg[u]; u = a[u]) {
            deg[u]--;
            if (dp[u] != 0) f = loop.size();
            loop.push_back(u);
        }
        if (f == -1) {
            if (loop.size() % 2 == 1) {
                cout << "-1\n";
                return;
            } else {
                for (int i = 0; i < (int) loop.size(); ++i) {
                    col[loop[i]] = i & 1;
                }
            }
        } else {
            int m = loop.size();
            for (int j = f; true; j = (j + 1) % m) {
                int u = loop[j];
                col[u] = dp[u] != 0;
                if (col[u] == 0) dp[a[u]]++;
                if (a[u] == loop[f]) break;
            }
        }
    }

    cout << n - accumulate(col.begin() + 1, col.end(), 0LL) << "\n";
    for (int i = 1; i <= n; ++i) {
        if (col[i] == 0) cout << a[i] << " ";
    }
    cout << "\n";
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T = 1;
    // cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}