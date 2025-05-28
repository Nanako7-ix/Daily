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
 * Created: 2025/05/21 14:32:50
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

struct KMP {
    int n;
    string s;
    vector<int> fail;

    KMP(string s) {
        this -> s = s;
        n = s.size();
        fail.assign(n, 0);
        for(int i = 1, j = 0; i < n; ++i) {
            while(j && s[i] != s[j]) j = fail[j - 1];
            fail[i] = j += (s[i] == s[j]);
        }
    }
    
    vector<array<int, 2>> match(string t) {
        int m = t.size();
        vector<array<int, 2>> ans;
        for(int i = 0, j = 0; i < m; ++i) {
            while(j && t[i] != s[j]) j = fail[j - 1];
            j += (t[i] == s[j]);
            if(j == n) {
                ans.push_back({i - j + 1, i});
                j = fail[j - 1];
            }
        }
        return ans;
    }
};

void solve() {
    int n;
    string s;
    cin >> n >> s;

    KMP kmp(s);
    auto fail = kmp.fail;

    // 需要求的是最小的非零 Border 而非最大的 Border
    // 那么显然可以通过跳 Border 的方式来做
    // 可以通过记忆化来优化
    // 如果最大 Border 非 0, 那么最小 Border 也非 0
    i64 sum = 0;
    vector<int> ans(n);
    for (int i = 0; i < n; ++i) {
        if (fail[i] == 0) {
            ans[i] = 0;
        } else {
            ans[i] = ans[fail[i] - 1] == 0 ? fail[i] : ans[fail[i] - 1];
        }
        sum += ans[i] == 0 ? 0 : i + 1 - ans[i];
    }
    cout << sum << endl;
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