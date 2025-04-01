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

template<typename T>
struct Discrete {
    int ok;
    vector<T> a;

    Discrete() {
        init();
    }

    void init() {
        ok = 0, a.clear();
    }

    void insert(const T& v) {
        assert(!ok);
        a.push_back(v);
    }

    void work() {
        ok = 1;
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
    }

    int lower_bound(const T& v) {
        if(!ok) work();
        return ::lower_bound(a.begin(), a.end(), v) - a.begin() + 1;
    }

    int upper_bound(const T& v) {
        if(!ok) work();
        return ::upper_bound(a.begin(), a.end(), v) - a.begin() + 1;
    }

    T operator[](int k) {
        if(!ok) work();
        return a[k - 1];
    }

    int size() {
        if(!ok) work();
        return a.size();
    }
};

void solve() {
    int n;
    cin >> n;
    Discrete<int> dis;
    vector<array<int, 2>> a(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i][0] >> a[i][1];
        dis.insert(a[i][0]);
        dis.insert(a[i][1]);
    }
    int m = dis.size();
    vector<vector<int>> in(m + 1), out(m + 1);
    for(int i = 1; i <= n; ++i) {
        a[i][0] = dis.lower_bound(a[i][0]);
        a[i][1] = dis.lower_bound(a[i][1]);
        in[a[i][0]].push_back(i);
        out[a[i][1]].push_back(i);
    }

    vector<int> col(n + 1);
    vector<int> now;
    col[1] = 1;
    for(int i = 1; i <= m; ++i) {
        for(auto x : in[i]) now.push_back(x);
        if(now.size() > 2) {
            cout << "-1\n";
            return;
        }
        if(now.size() == 2) {
            col[now[1]] = col[now[0]] ^ 1;
        }
        for(auto x : out[i]) {
            now.erase(find(now.begin(), now.end(), x));
        }
    }

    cout << accumulate(col.begin() + 1, col.end(), 0) << endl;
    for(int i = 1; i <= n; ++i) {
        if(col[i]) cout << i << ' ';
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}