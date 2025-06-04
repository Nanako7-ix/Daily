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
 * Created: 2025/06/04 19:25:05
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

vector<int> zFunction(const string& s) {
    int n = s.size();
    vector<int> z(n);
    z[0] = n;
    for(int i = 1, j = 1; i < n; ++i) {
        z[i] = max(0, min(z[i - j], j + z[j] - i));
        while(i + z[i] < n && s[i + z[i]] == s[z[i]]) z[i]++;
        if(i + z[i] > j + z[j]) j = i;
    }
    return z;
};

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    vector<int> fail(n);
    for (int i = 1, j = 0; i < n; ++i) {
        while (j && s[i] != s[j]) j = fail[j - 1];
        fail[i] = j += (s[i] == s[j]);
    }

    vector<int> border;
    for (int i = n; i; i = fail[i - 1]) {
        border.push_back(i);
    } border.push_back(0);

    auto f = zFunction(s);
    for (int i = 0; i < n; ++i) {
        f[i] = *lower_bound(border.begin(), border.end(), f[i], greater {});
    }

    vector<int> id(n);
    iota(id.begin(), id.end(), 0);
    sort(id.begin(), id.end(), [&](int i, int j) -> bool {
        return f[i] > f[j];
    });
    
    int ans = n;
    set<int> pos { 0, n };
    multiset<int> dis { n };
    for (int i = 1, Min = n; i < n; ++i) {
        int u = id[i];
        Min = min(Min, f[u]);

        auto nxt = pos.lower_bound(u);
        auto pre = prev(nxt);
        pos.insert(u);

        dis.erase(dis.find(*nxt - *pre));
        dis.insert(*nxt - u);
        dis.insert(u - *pre);

        if (*dis.rbegin() <= Min) {
            ans = min(ans, Min);
        }
    }
    cout << ans << "\n";
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