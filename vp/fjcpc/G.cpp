#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

int main () {
    cin.tie(nullptr), cout.tie(nullptr) -> sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    vector<i64> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    vector<i64> pre(n + 1);
    for (int i = 2; i <= n; ++i) {
        pre[i] = pre[i - 1] + max(a[i] - a[i - 1], 0LL);
    }

    int add; cin >> add;
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << add + pre[r] - pre[l] << "\n";
    }
}