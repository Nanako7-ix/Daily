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
    int ready;
    vector<T> a;

    Discrete() {
        init();
    }

    void init() {
        ready = 0, a.clear();
    }

    void insert(const T& v) {
        assert(!ready);
        a.push_back(v);
    }

    void work() {
        ready = 1;
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
    }

    int lower_bound(const T& v) {
        if(!ready) work();
        return ::lower_bound(a.begin(), a.end(), v) - a.begin() + 1;
    }

    int upper_bound(const T& v) {
        if(!ready) work();
        return ::upper_bound(a.begin(), a.end(), v) - a.begin() + 1;
    }

    T operator[](int k) {
        if(!ready) work();
        return a[k - 1];
    }

    int size() {
        if(!ready) work();
        return a.size();
    }
};

void solve() {
    int n;
    cin >> n;
    vector<string> s(n + 1);
    Discrete<string> dis;
    for(int i = 1; i <= n; ++i) {
        cin >> s[i];
        dis.insert(s[i]);
    }

    vector<int> a(n + 1);
    for(int i = 1; i <= n; ++i) {
        a[i] = dis.lower_bound(s[i]);
    }
    vector<int> l(n + 1, 1), r(n + 1, 1);
    l[0] = r[0] = 0;
    for(int i = 1; i <= n; ++i) {
        if(i != 1 && a[i] == a[i - 1]) {
            l[i] = l[i - 1] + 1;
        }
    }
    for(int i = n; i >= 1; --i) {
        if(i != n && a[i] == a[i + 1]) {
            r[i] = r[i + 1] + 1;
        }
    }
    int ans = max(*max_element(l.begin() + 1, l.end()), *max_element(r.begin() + 1, r.end()));
    for(int i = 2; i < n; ++i) {
        if(a[i - 1] == a[i + 1]) {
            ans = max(ans, l[i - 1] + r[i + 1]);
        }
    }
    cout << ans << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}