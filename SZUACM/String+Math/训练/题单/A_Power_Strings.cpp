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
 * Created: 2025/05/17 16:04:53
 * 好想和 めぐる 一起打 xcpc 啊
 */
#include <iostream>
#include <vector>
#include <cassert>
#define setpre(x) fixed << setprecision(x)
#define debug(x) cerr << #x << " = " << x << "\n"
#define endl "\n"
using namespace std;

struct KMP {
    int n;
    string s;
    vector<int> nxt;

    KMP(string s) {
        this -> s = s;
        n = s.size();
        nxt.assign(n, 0);
        for(int i = 1, j = 0; i < n; ++i) {
            while(j && s[i] != s[j]) j = nxt[j - 1];
            nxt[i] = j += (s[i] == s[j]);
        }
    }
};

void solve() {
    while (true) {
        string s;
        cin >> s;
        int n = s.size();
        if (s == ".") break;
        KMP kmp(s);
        vector<int> nxt = kmp.nxt;
        int border = nxt[n - 1];
        while (n % (n - border) != 0) {
            border = nxt[border - 1];
        }
        cout << n / (n - border) << endl;
    }
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