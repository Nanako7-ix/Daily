#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#define setpre(x) fixed << setprecision(x)
#define debug(x) cerr << #x << " = " << x << "\n"
#define endl "\n"
using namespace std;
using namespace __gnu_pbds;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

constexpr int inf = 0x3f3f3f3f;
constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;

vector<int> f (vector<int> a) {
    int n = a.size() - 1;
    vector<int> op;
    auto work = [&](int p) -> void {
        op.push_back(p);
        vector<int> b(n + 1);
        for(int i = 1; i < p; ++i) {
            b[n - p + i + 1] = a[i];
        }
        b[n - p + 1] = a[p];
        for(int i = p + 1; i <= n; ++i) {
            b[i - p] = a[i];
        }
        swap(a, b);
    };
    for(int i = n; i > 1; --i) {
        int p = find(a.begin() + 1, a.end(), i) - a.begin();
        if(p != 1) work(p - 1);
        p = find(a.begin() + 1, a.end(), i - 1) - a.begin();
        work(p);
    }
    return op;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1), b(m + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for(int i = 1; i <= m; ++i) {
        cin >> b[i];
    }
    auto op1 = f(a), op2 = f(b);

    if(op1.size() % 2 != op2.size() % 2) {
        if(n & 1) {
            for(int i = 1; i <= n; ++i) {
                op1.push_back(n);
            }
        } else if(m & 1) {
            for(int i = 1; i <= m; ++i) {
                op2.push_back(m);
            }
        }
    }

    if(op1.size() % 2 == op2.size() % 2) {
        while(op1.size() < op2.size()) {
            op1.push_back(1);
            op1.push_back(n);
        }
        while(op2.size() < op1.size()) {
            op2.push_back(m);
            op2.push_back(1);
        }
        cout << op1.size() << endl;
        for(int i = 0; i < (int) op1.size(); ++i) {
            cout << op1[i] << ' ' << op2[i] << endl;
        }
    } else {
        cout << "-1\n";
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}