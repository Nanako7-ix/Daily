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
    cout << s;
    auto r = Manacher(s);
    int m = r.size(), n = s.size();
    for(int i = 0; i < m; ++i) {
        if(i / 2 + r[i] / 2 == n) {
            string t = s.substr(0, i - n);
            reverse(t.begin(), t.end());
            cout << t; break;
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