#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr int N = 100005;
constexpr int T = 50005;
constexpr double inf = 4E18;

double k[N], b[N];
int seg[T << 2];

double eval(int i, int p) {
    return k[i] * p + b[i];
}

void insert(int l, int r, int u, int p) {
    int m = (l + r) >> 1;
    if (eval(seg[u], m) < eval(p, m)) {
        swap(seg[u], p);
    }
    if (l == r) return;
    if (eval(seg[u], l) < eval(p, l)) {
        insert(l, m, u << 1, p);
    }
    if (eval(seg[u], r) < eval(p, r)) {
        insert(m + 1, r, u << 1 | 1, p);
    }
}

double query(int l, int r, int u, int p) {
    if (l == r) return eval(seg[u], p);
    double ans = eval(seg[u], p);
    int m = (l + r) >> 1;
    if (p <= m) {
        ans = max(ans, query(l, m, u << 1, p));
    } else {
        ans = max(ans, query(m + 1, r, u << 1 | 1, p));
    }
    return ans;
}

void Thephix() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        string op;
        cin >> op;
        if (op == "Project") {
            cin >> b[i] >> k[i];
            b[i] -= k[i];
            insert(1, T, 1, i);
        } else {
            int p; cin >> p;
            double ans = query(1, T, 1, p);
            cout << int(ans / 100) << "\n";
        }
    }
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