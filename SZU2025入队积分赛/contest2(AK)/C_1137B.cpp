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

struct KMP : string {
    vector<int> nxt;
    KMP(string s) : string(s), nxt(size()) {
        int n = s.size();
        for(int i = 1, j = 0; i < n; ++i) {
            while(j && at(i) != at(j)) j = nxt[j - 1];
            nxt[i] = j += (at(i) == at(j));
        }
    }
    vector<int> work(string s) {
        int n = s.size();
        vector<int> res;
        for(int i = 0, j = 0; i < n; ++i) {
            while(j && s[i] != at(j)) j = nxt[j - 1];
            j += (s[i] == at(j));
            if(j == (int) size()) res.push_back(i - j + 1), j = nxt[j - 1];
        }
        return res;
    }
};

void solve() {
    string s, t;
    cin >> s >> t;
    KMP kmp(t);
    int len = kmp.nxt.back();
    array<int, 2> cnt {0, 0};
    for(auto c : s) cnt[c - '0']++;
    for(int i = 0; cnt[0] > 0 || cnt[1] > 0;) {
        if(cnt[0] == 0) {
            cout << 1;
            cnt[1]--;
        } else if(cnt[1] == 0) {
            cout << 0;
            cnt[0]--;
        } else {
            cout << t[i];
            cnt[t[i] - '0']--;
            i++;
            if(i == t.size()) i = len;
        }
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}