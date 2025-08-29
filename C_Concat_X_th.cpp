#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

void Thephix() {
    int n, k, x;
    cin >> n >> k >> x;
    vector<string> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    vector<string> ans;
    vector<int> p(k + 1);
    auto dfs = [&](auto&& dfs, int i) -> void {
        if (i == k + 1) {
            string res;
            for (int j = 1; j <= k; ++j) {
                res += a[p[j]];
            }
            ans.push_back(res);
            return;
        }
        for (int j = 1; j <= n; ++j) {
            p[i] = j;
            dfs(dfs, i + 1);
        }
    };

    dfs(dfs, 1);
    sort(ans.begin(), ans.end());
    cout << ans[x - 1] << "\n";
}

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T = 1;
    // cin >> T;

    while (T--) {
        Thephix();
    }

    return 0;
}