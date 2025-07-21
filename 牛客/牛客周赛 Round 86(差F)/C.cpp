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

void solve() {
    int n, now = 1;
    string s;
    cin >> n >> s;
    vector<int> a;
    for(int i = 1; i < n; ++i) {
        if(s[i] != s[i - 1]) {
            a.push_back(now);
            now = 1;
        } else now++;
    }
    a.push_back(now);
    vector<int> b;
    for(int i = 0; i < (int) a.size(); ++i) {
        b.push_back(a[i]);
        while(!b.empty() && b.back() % 2 == 0 && i != a.size() - 1) {
            b.pop_back();
            if(!b.empty()) b.back() += a[++i];
        }
    }
    if(!b.empty() && b.back() % 2 == 0) b.pop_back();
    cout << b.size() / 2 << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}