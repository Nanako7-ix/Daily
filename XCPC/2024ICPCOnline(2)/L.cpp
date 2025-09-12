#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

template<std::unsigned_integral T>
constexpr T floor_sqrt (T n) {
	T t = std::sqrt(n);
	while (t * t > n) --t;
	while ((t + 1) * (t + 1) < n) ++t;
	return t;
}

template<std::unsigned_integral T>
constexpr T ceil_sqrt (T n) {
	T t = std::sqrt(n);
	while (t * t < n) ++t;
	while ((t - 1) * (t - 1) >= n) --t;
	return t;
}

void Thephix() {
	i64 T;
	cin >> T;

	auto f = [&](i64 k) -> array<i64, 2> {
		return {
			2 * T + k + k * k - 2 * k,
			2 * k
		};
	};

	auto x = f(floor_sqrt<u64>(2 * T));
	auto y = f( ceil_sqrt<u64>(2 * T));

	if ((i128) x[0] * y[1] <= (i128) y[0] * x[1]) {
		i64 d = gcd(x[0], x[1]);
		cout << x[0] / d << ' ' << x[1] / d << "\n";
	} else {
		i64 d = gcd(y[0], y[1]);
		cout << y[0] / d << ' ' << y[1] / d << "\n";
	}
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
