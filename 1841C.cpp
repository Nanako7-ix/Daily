#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

int f[5] = {1, 10, 100, 1000, 10000};

void Thephix() {
    string s;
    cin >> s;

    int n = s.size();
    vector<int> a(n + 1);
    array<vector<int>, 5> p1 {}, p2 {};
    for (int i = 1; i <= n; ++i) {
        a[i] = s[i - 1] - 'A';
        p1[a[i]].push_back(i);
        for (int j = 0; j < a[i]; ++j) {
            p2[j].push_back(i);
        }
    }

    auto get = [&](int p, int x) {
        for (int i = 0; i < a[p]; ++i) {
            if (!p2[i].empty() && p2[i].back() == p) {
                p2[i].pop_back();
            }
        }
        for (int i = 0; i < x; ++i) {
            if (p2[i].empty() || p2[i].back() < p) {
                p2[i].push_back(p);
            }
        }

        i64 res = 0;
        for (int i = 0; i < 5; ++i) {
            int cnt = lower_bound(p1[i].begin(), p1[i].end(), min(i, p2[i].empty() ? 0 : p2[i].back())) - p1[i].begin();
            res -= 2LL * f[i] * cnt;
        }

        for (int i = 0; i < x; ++i) {
            if (!p2[i].empty() && p2[i].back() == p) {
                p2[i].pop_back();
            }
        }
        for (int i = 0; i < a[p]; ++i) {
            if (p2[i].empty() || p2[i].back() < p) {
                p2[i].push_back(p);
            }
        }
        return res;
    };

    i64 sum = 0, ans = 0;
    for (int i = 1; i <= n; ++i) {
        int x = f[a[i]];
        if (upper_bound(p2[a[i]].begin(), p2[a[i]].end(), i) != p2[a[i]].end()) {
            x *= -1;
        }
        sum += x;
        i64 res = get(i, a[i]);
        for (int j = 0; j < 5; ++j) {
            int y = f[j];
            if (upper_bound(p2[j].begin(), p2[j].end(), i) != p2[j].end()) {
                y *= -1;
            }
            ans = max(ans, y - x + get(i, j) - res);
        }
    }

    cout << sum + ans << "\n";
}

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T = 1;
    cin >> T;

    while (T--) {
        Thephix();
    }

    return 0;
}