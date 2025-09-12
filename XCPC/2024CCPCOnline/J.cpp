#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

template<int N>
struct Basis : std::array<u64, N> {
	using std::array<u64, N>::at;

	Basis() : std::array<u64, N>() {}
	
	void insert(u64 x) {
		for (int i = N - 1; i >= 0; --i) {
			if (x >> i & 1) {
				if (at(i) == 0) {
					at(i) = x;
					break;
				}
				x ^= at(i);
			}
		}
	}

	bool exist(u64 x) {
		for (int i = N - 1; i >= 0; --i) {
			if (x >> i & 1) {
				if (at(i) == 0) {
					return false;
				}
			}
		}
		return true;
	}
};

constexpr int N = 31;

void Thephix() {
	int n, A = 0, B = 0;
	cin >> n;
	vector<int> a(n + 1), b(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		A ^= a[i];
	}
	for (int i = 1; i <= n; ++i) {
		cin >> b[i];
		B ^= b[i];
	}

	Basis<N> basis {};
	for (int i = 1; i <= n; ++i) {
		basis.insert(a[i] ^ b[i]);
	}
	
	int p = __lg(A ^ B);
	
	auto f = [&](int x, int y) {
		for (int i = N - 1; i >= 0; --i) {
			if (i == p) continue;
			if (x < y) swap(x, y);
			if (x >> i & 1) {
				x ^= basis[i];
				y ^= basis[i];
			}
		}
		return max(x, y);
	};
	
	cout << min(f(A, B), f(A ^ basis[max(p, 0)], B ^ basis[max(p, 0)])) << "\n";
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
