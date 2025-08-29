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
    int n;
    string s;
    cin >> n >> s;
    vector<int> pre(n + 1);
    for (int i = 1; i <= n; ++i) {
        pre[i] = pre[i - 1] + (s[i - 1] == '0');
    }

    i64 ans = 0;
    array<int, 2> cnt {1, 0};
    for (int i = 1; i <= n; ++i) {
        ans += cnt[pre[i] & 1]++;
    }
    cout << ans << "\n";
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