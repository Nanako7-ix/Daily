#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

i64 solve() {
    i64 a, b;
    cin >> a >> b;
    if (a % b == 0) return -1;
    i64 d = gcd(a, b);
    i64 ans = b / d;
    while (gcd(ans, d) != 1) {
        ans /= gcd(ans, d);
    }
    return ans == 1 ? -1 : ans;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t; cin >> t;
    while (t--) {
        cout << solve() << '\n';
    }
    return 0;
}