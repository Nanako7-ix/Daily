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
    vector f (26, vector<int> (26));
    string s;
    int n, q;
    cin >> n >> q >> s;

    array<int, 26> cnt {};
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < 26; ++j) {
            f[s[i] - 'a'][j] += cnt[j];
        }
        cnt[s[i] - 'a']++;
    }

    while(q--) {
        cin >> s;
        i64 ans = 0;
        auto g = f;
        for(int i = 0; i < 26; ++i) {
            int x = s[i] - 'a';
            for(int j = 0; j < 26; ++j) {
                if(j == x) continue;
                ans += g[x][j];
            }
            for(int j = 0; j < 26; ++j) {
                g[j][x] = 0;
            }
        }
        cout << ans << endl;
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}