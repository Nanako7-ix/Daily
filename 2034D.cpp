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
    int n;
    cin >> n;
    vector<int> a(n + 1);
    array<set<int>, 3> S;
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
        S[a[i]].insert(i);
    }
    
    auto now = [&]() -> int {
        if(S[2].size()) return 2;
        if(S[1].size()) return 1;
        return 0;
    };
    auto swap = [&](int x, int y) -> void {
        S[a[x]].erase(x), S[a[x]].insert(y);
        S[a[y]].erase(y), S[a[y]].insert(x);
        ::swap(a[x], a[y]);
    };

    vector<array<int, 2>> ans;
    for(int i = n; i >= 1; --i) {
        while(a[i] != now()) {
            int p = *S[a[i] + 1].begin();
            swap(p, i);
            ans.push_back({p, i});
        }
        S[now()].erase(i);
    }

    cout << ans.size() << endl;
    for(auto [x, y] : ans) {
        cout << x << ' ' << y << endl;
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}