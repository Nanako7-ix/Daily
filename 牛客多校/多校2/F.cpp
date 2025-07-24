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
    int n, t;
    string s;
    cin >> n >> t >> s;

    if (t >= n - 1) {
        cout << "0\n";
        return;
    }

    vector<int> p;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '1') {
            p.push_back(i);
        }
    }

    auto find = [&](int pos) {
        auto it = lower_bound(p.begin(), p.end(), pos);
        if (it == p.end()) return pair { p.back(), p[0] };
        if (*it == pos) return pair { *it, *it };
        int prv;
        if (it == p.begin()) {
            prv = p.back();
        } else prv = *prev(it);
        return pair { prv, *it };
    };

    int ans = 0;
    vector<array<int, 2>> from(n);
    for (int i = 0; i < n; ++i) {
        auto [prv, nxt] = find(i);
        if (prv > i) prv -= n;
        if (nxt < i) nxt += n;
        from[i][0] = prv + t >= i;
        from[i][1] = nxt - t <= i;
        ans += from[i][0] | from[i][1];
    }

    int res = 0;
    for (int i = 0; i < n; ++i) {
        if (from[i][0] == from[i][1]) {
            continue;
        }
        auto [prv, nxt] = find(i);
        if (prv > i) prv -= n;
        if (nxt < i) nxt += n;
        if (from[i][0]) {
            res = max(res, min(nxt - t - 1, prv + t) - i);
        } else {
            res = max(res, i - max(nxt - t, prv + t + 1));
        }
    }
    cout << (n - ans) + res << "\n";
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