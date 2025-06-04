#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

void solve() {
    int n;
    cin >> n;
    vector<i64> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    vector<int> lft(n + 1);
    map<int, vector<array<int, 2>>> mp;
    for (int i = 1; i <= n; ++i) {
        if (a[i] != a[i - 1]) {
            lft[i] = i;
        } else {
            lft[i] = lft[i - 1];
        }
        auto& v = mp[a[i]];
        if (v.empty()) {
            v.push_back({i, i});
        } else {
            auto& [l, r] = v.back();
            if (r != i - 1) {
                v.push_back({i, i});
            } else {
                v.back()[1]++;
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        i64 w; cin >> w;
        auto& v = mp[i];

        // 排除不需要操作的情况
        if (!v.empty() && v.back() == array<int, 2> {1, n}) {
            cout << 0 << endl;
            continue;
        }

        // 至少需要操作一次
        int len = n, cnt = 1;
        for (auto [l, r] : v) {
            if (l == 1 || r == n) {
                len -= r - l + 1;
                continue;
            }
            // 如果中间的太长了，那么中间不需要操作，操作次数+1，操作长度减小
            if (r - l + 1 > w) {
                cnt++, len -= r - l + 1;
            }
        }
        cout << len + cnt * w << " \n"[i == n];
    }
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    solve();
}