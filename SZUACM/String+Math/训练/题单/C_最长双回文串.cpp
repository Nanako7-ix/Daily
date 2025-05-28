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
 * Created: 2025/05/17 16:21:45
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

vector<int> Manacher(const string& p) {
    string s = "#";
    for(auto c : p) s += c, s += '#';
    int n = s.size();
    vector<int> r(n);
    for(int i = 0, j = 0; i < n; ++i) {
        r[i] = i < j + r[j] ? min(r[2 * j - i], j + r[j] - i) : 1;
        while(i + r[i] < n && i - r[i] >= 0 && s[i + r[i]] == s[i - r[i]]) ++r[i];
        if(i + r[i] > j + r[j]) j = i;
    }
    return r;
};

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    auto d = Manacher(s);
    vector<int> minl(n, inf), maxr(n);
    for (int i = 1; i < 2 * n; ++i) {
        int l = (i - d[i] + 1) / 2;
        int r = (i + d[i]) / 2 - 1;
        if (r - l + 1 <= 0) continue;
        minl[r] = min(minl[r], l);
        maxr[l] = max(maxr[l], r);
    }

    int ans = 0, Max = maxr[0] + 1;
    for (int i = 0; i < n; ++i) {
        Max -= 2;
        if (i + 1 < n) Max = max(Max, maxr[i + 1] - i);
        ans = max(ans, Max + i - minl[i] + 1);
    }
    cout << ans << endl;
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