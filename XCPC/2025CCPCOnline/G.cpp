#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

template <typename Val>
struct HashMap {
  HashMap(u32 n = 0) { build(n); }
  void build(u32 n) {
    u32 k = 8;
    while (k < n * 2) k *= 2;
    cap = k / 2, mask = k - 1;
    key.resize(k);
		val.resize(k);
		used.assign(k, 0);
  }

  void clear() {
    used.assign(used.size(), 0);
    cap = (mask + 1) / 2;
  }

  int size() {
		return used.size() / 2 - cap;
	}

  int index(const u64& k) {
    int i = 0;
    for (i = hash(k); used[i] && key[i] != k; i = (i + 1) & mask) {}
    return i;
  }

  Val& operator[](const u64& k) {
    if (cap == 0) extend();
    int i = index(k);
    if (!used[i]) { used[i] = 1, key[i] = k, val[i] = Val{}, --cap; }
    return val[i];
  }

	Val get(const u64& k) {
    int i = index(k);
    return (used[i] ? val[i] : Val {});
  }
	
  Val get(const u64& k, Val default_value) {
    int i = index(k);
    return (used[i] ? val[i] : default_value);
  }

  bool count(const u64& k) {
    int i = index(k);
    return used[i] && key[i] == k;
  }

	template <typename F>
  void enumerate_all(F f) {
    for (int i = 0; i < (int) used.size(); ++i) {
			if (used[i]) f(key[i], val[i]);
		}
  }
private:
  u32 cap, mask;
  vector<u64> key;
  vector<Val> val;
  vector<bool> used;

  u64 hash(u64 x) {
    static const u64 FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
    x += FIXED_RANDOM;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return (x ^ (x >> 31)) & mask;
  }

  void extend() {
    vector<pair<u64, Val>> dat;
    dat.reserve(used.size() / 2 - cap);
    for(int i = 0; i < (int) used.size(); ++i) {
      if (used[i]) dat.emplace_back(key[i], val[i]);
    }
    build(2 * dat.size());
    for (auto& [a, b]: dat) (*this)[a] = b;
  }
};

void Thephix() {
	int n, q;
	cin >> n >> q;
	vector<i64> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}

	const int B = 330, N = (n + B - 1) / B;
	vector<HashMap<i64>> f(N + 1), cnt(N + 1);
	for (int i = 1; i <= N; ++i) {
		int l = (i - 1) * B + 1;
		int r = min(i * B, n);
		for (int x = l; x < r; ++x) {
			for (int y = x + 1; y <= r; ++y) {
				f[i][a[x] << 32 | a[y]]++;
			}
			cnt[i][a[x]]++;
		}
		cnt[i][a[r]]++;
	}

	while (q--) {
		i64 x, y, ans = 0;
		cin >> x >> y;
		for (int i = 1; i <= N; ++i) {
			ans += f[i].get(x << 32 | y);
		}
		i64 cnt_y = cnt[N].get(y);
		for (int i = N - 1; i >= 1; --i) {
			ans += cnt[i].get(x) * cnt_y;
			cnt_y += cnt[i].get(y);
		}
		cout << ans << "\n";
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
