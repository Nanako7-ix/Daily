#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

template<typename T>
struct Point {
	using value_type = T;
	T x, y;
	Point () : x(0), y(0) {}
	Point (const T& x, const T& y) : x(x), y(y) { }
	
	T   dot(const Point& o) const { return x * o.x + y * o.y; }
	T cross(const Point& o) const { return x * o.y - y * o.x; }

	Point  operator- () const { return Point { -x, -y }; }
	Point& operator+=(const Point& o) & { x += o.x, y += o.y; return *this; }
	Point& operator-=(const Point& o) & { x -= o.x, y -= o.y; return *this; }
	Point& operator*=(const T& k) & { x *= k, y *= k; return *this; }
	Point& operator/=(const T& k) & { x /= k, y /= k; return *this; }
	
	friend Point operator+(Point x, const Point& y) { return x += y; }
	friend Point operator-(Point x, const Point& y) { return x -= y; }
	friend Point operator*(Point p, const T& k) { return p *= k; }
	friend Point operator*(const T& k, Point p) { return p *= k; }
	friend Point operator/(Point p, const T& k) { return p /= k; }
	
	friend bool operator== (const Point& x, const Point& y) { return x.x == y.x && x.y == y.y; }
	friend auto operator<=>(const Point& x, const Point& y) = default;
	
	friend std::istream& operator>> (std::istream& is, Point& p) { return is >> p.x >> p.y; }
	friend std::ostream& operator<< (std::ostream& os, const Point& p) { return os << "(" << p.x << ", " << p.y << ")"; }

	T square() const { return dot(*this); }
	double length() const { return std::sqrt(dot(*this)); }
	double angle() const { return std::atan2(y, x); }

	Point<double> rotate(double k) const {
		return Point<double>(
			x * std::cos(k) - y * std::sin(k),
			x * std::sin(k) + y * std::cos(k)
		);
	}

	template<typename U> operator Point<U>() const { return Point<U> (U(x), U(y)); }
};

void Thephix() {
	int n;
	cin >> n;
	vector<Point<i64>> a(n + 1);
	vector<int> p;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		if (!p.empty() && a[p.back()].y == a[i].y) {
			p.pop_back();
		}
		p.push_back(i);
	}

	if (a[p.back()].y == a[p.front()].y) {
		p.pop_back();
	}

	auto check = [&](int j) {
		int i = j - 1; if (i < 1) i = n;
		int k = j + 1; if (k > n) k = 1;
		return (a[j] - a[i]).cross(a[k] - a[j]) > 0;
	};

	int ans = 0;
	int m = p.size();
	for (int i = 0; i < m; ++i) {
		int x = p[(i - 1 + m) % m];
		int y = p[i];
		int z = p[(i + 1) % m];
		if (a[x].y > a[y].y && a[z].y > a[y].y) {
			ans += check(y);
		}
	}
	cout << ans << "\n";
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
