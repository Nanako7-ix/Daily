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

int solve() {
    int n, k;
    string s;
    cin >> n >> k >> s;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    int l = 1, r = n, res = -1;
    while(l <= r && s[l - 1] == 'R') l++;
    while(l <= r && s[r - 1] == 'R') r--;
    if(l > r) return 0;

    vector<int> b;
    b.push_back(a[l]);
    for(int i = l + 1; i <= r; ++i) {
        if(s[i - 1] == s[i - 2]) {
            b.back() = max(b.back(), a[i]);
        } else {
            b.push_back(a[i]);
        }
    }

    auto check = [&](int x) -> int {
        int ans = 0, on = 0;
        for(int i = 0; i < (int) b.size(); ++i) {
            if(i & 1) {
                if(b[i] > x && on) {
                    ans++, on = 0;
                }
            } else if(b[i] > x) {
                on = 1;
            }
        }
        return ans + on <= k;
    };

    l = 0, r = 1e9;
    while(l <= r) {
        int m = (l + r) >> 1;
        if(check(m)) {
            res = m, r = m - 1;
        } else l = m + 1;
    }

    return res;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) cout << solve() << endl;
    return 0;
}