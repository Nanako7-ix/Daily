#include <bits/stdc++.h>
using namespace std;

int holes_cnt[26] = {1, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0};

int main () {
    cin.tie(nullptr), cout.tie(nullptr) -> sync_with_stdio(false);
    string s;
    cin >> s;
    int ans = 0, n = s.size();
    for (int _ = 0; _ < 26; ++_) {
        int res = 0;
        for (int i = 0; i < n; ++i) {
            res += holes_cnt[s[i] - 'A'];
            s[i] = (s[i] - 'A' + 1) % 26 + 'A';
        }
        ans = max(ans, res);
    }
    cout << ans << "\n";
}