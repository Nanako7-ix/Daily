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
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    int l = 1, r = n, last = -1, st;
    auto L = [&]() {
        cout << 'L';
        st = a[l] > last;
        last = a[l];
        l++;
    };
    auto R = [&]() {
        cout << 'R';
        st = a[r] > last;
        last = a[r];
        r--;
    };
    
    while (l <= r) {
        if (last == -1) {
            L();
        } else {
            if (min(a[l], a[r]) > last) {
                if (a[l] > a[r]) L();
                else R();
            } else if (max(a[l], a[r]) < last) {
                if (a[l] < a[r]) L ();
                else R();
            } else {
                if (st == 0) {
                    if (a[l] > last) {
                        L();
                    } else R();
                } else {
                    if (a[r] > last) {
                        L();
                    } else R();
                }
            }
        }
    }
    cout << "\n";
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