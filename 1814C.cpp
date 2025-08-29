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
 * Created: 2025/07/12 00:43:34
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

pair<i64, int> nmsl(int n, vector<array<int, 2>>& a, int s1, int s2) {
    pair<i64, int> ans {0, n};
    vector<i64> pre(n + 1);
    for (int i = 1; i <= n; ++i) {
        pre[i] = pre[i - 1] + a[i][0];
        ans.first += 1LL * s1 * i * a[i][0];
    }

    for (int i = 1; i <= n; ++i) {
        int insert = i * s2;
        int k = (insert + s1 - 1) / s1;
        i64 res = ans.first;
        if (k <= n - i + 1) {
            res -= s1 * (pre[n] - pre[k + i - 1]);
            res += 1LL * a[k + i - 1][0] * (i * s2 - k * s1);
        } else {
            break;
        }
        if (res < ans.first) {
            ans.first = res;
            ans.second = n - i;
        }
    }

    return ans;
}

void solve() {
    int n, s1, s2;
    cin >> n >> s1 >> s2;
    vector<array<int, 2>> a(n + 1);
    vector<i64> pre(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i][0];
        a[i][1] = i;
    }
    sort(a.begin() + 1, a.end(), greater {});

    int cnt = min(nmsl(n, a, s1, s2).second, n - nmsl(n, a, s2, s1).second);
    vector<int> x, y;
    vector<array<int, 2>> cnm(n + 1);
    for (int i = 1; i <= n; ++i) {
        if (i <= cnt) {
            cnm[i] = { s1 * i, 0 };
        } else {
            cnm[i] = { s2 * (i - cnt), 1 };
        }
    }
    sort(cnm.begin() + 1, cnm.end());
    for (int i = 1; i <= n; ++i) {
        if (cnm[i][1] == 0) {
            x.push_back(a[i][1]);
        } else {
            y.push_back(a[i][1]);
        }
    }

    cout << x.size() << " ";
    for (auto _ : x) cout << _ << ' ';
    cout << "\n";
    cout << y.size() << " ";
    for (auto _ : y) cout << _ << ' ';
    cout << "\n";
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