#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

std::vector<int> minp, P;
std::vector<vector<int>> fac;

void sieve(int N) {
    minp.assign(N + 1, 0);
    fac.assign(N + 1, {});
    P.clear();
    for (int i = 2; i <= N; ++i) {
        if (minp[i] == 0) {
            P.push_back(minp[i] = i);
        }
        for (i64 p : P) {
            if(i * p > N) break;
            minp[i * p] = p;
            if(i % p == 0) break;
        }

        int x = i, p = minp[i];
        while (x % p == 0) {
            x /= p;
        }
        fac[i] = fac[x];
        fac[i].push_back(p);
        sort(fac[i].begin(), fac[i].end());
        fac[i].erase(unique(fac[i].begin(), fac[i].end()), fac[i].end());
    }
}

void Thephix() {
    int n, m;
    cin >> n >> m;
    vector<int> cnt(m + 1);

    auto update = [&](int x, int d) -> void {
        int tot = fac[x].size();
        for (int s = 1; s < (1 << tot); ++s) {
            int mul = 1;
            for (int j = 0; j < tot; ++j) {
                if (s >> j & 1) {
                    mul *= fac[x][j];
                }
            }
            cnt[mul] += d;
        }
    };

    auto check = [&](int x) -> int {
        if (x == 1) return 0;
        int ans = 0, tot = fac[x].size();
        for (int s = 1; s < (1 << tot); ++s) {
            int mul = 1;
            for (int j = 0; j < tot; ++j) {
                if (s >> j & 1) {
                    mul *= fac[x][j];
                }
            }
            if (popcount<u32> (s) & 1) {
                ans += cnt[mul];
            } else ans -= cnt[mul];
        }
        return ans;
    };
    
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        update(a[i], 1);
    }

    int x1 = -1, y1 = -1, x2 = -1, y2 = -1;
    for (int i = 1; i <= n; ++i) {
        if (check(a[i]) != n) {
            x1 = i;
            for (int j = 1; j <= n; ++j) {
                if (j != i && gcd(a[i], a[j]) == 1) {
                    y1 = j;
                    break;
                }
            }
            assert(y1 != -1);
            break;
        }
    }

    if (x1 == -1) {
        cout << "0\n";
        return;
    }

    update(a[x1], -1), update(a[y1], -1);
    for (int i = 1; i <= n; ++i) {
        if (i == x1 || i == y1) continue;
        if (check(a[i]) != n - 2) {
            x2 = i;
            for (int j = 1; j <= n; ++j) {
                if (j == x1 || j == y1) continue;
                if (i != j && gcd(a[i], a[j]) == 1) {
                    y2 = j;
                    cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << "\n";
                    return;
                }
            }
        }
    }

    swap(x2, y1);
    if (check(a[x1]) == n - 2 || check(a[x2]) == n - 2) {
        cout << "0\n";
        return;
    }

    for (int i = 1; i <= n; ++i) {
        if (i == x1 || i == x2) continue;
        if (gcd(a[x1], a[i]) == 1) {
            y1 = i;
            break;
        }
    }
    update(a[y1], -1);
    if (check(a[x2]) != n - 3) {
        for (int i = 1; i <= n; ++i) {
            if (i == x1 || i == y1 || i == x2) continue;
            if (gcd(a[x2], a[i]) == 1) {
                y2 = i;
                break;
            }
        }
        cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << "\n";
        return;
    }
    update(a[y1], 1);

    swap(x1, x2);

    for (int i = 1; i <= n; ++i) {
        if (i == x1 || i == x2) continue;
        if (gcd(a[x1], a[i]) == 1) {
            y1 = i;
            break;
        }
    }
    update(a[y1], -1);
    if (check(a[x2]) != n - 3) {
        for (int i = 1; i <= n; ++i) {
            if (i == x1 || i == y1 || i == x2) continue;
            if (gcd(a[x2], a[i]) == 1) {
                y2 = i;
                break;
            }
        }
        cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << "\n";
        return;
    }
    update(a[y1], 1);

    cout << "0\n";
}

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    sieve(1E6);

    int T = 1;
    cin >> T;

    while (T--) {
        Thephix();
    }

    return 0;
}