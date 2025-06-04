#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
constexpr int inf = 2e9;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];

    if (n == 1) {
        cout << "1\n";
        return;
    }

    int Min = *min_element(a.begin(), a.end());
    int Max = *max_element(a.begin(), a.end());
    int ans = 4;

    if (a[0] == Min || a[n - 1] == Min) ans--;
    if (a[0] == Max || a[n - 1] == Max) ans--;

    cout << ans << "\n";
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(0);
    solve();
    return 0;
}