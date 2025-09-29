#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

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
	
	friend istream& operator>> (istream& is, Point& p) { return is >> p.x >> p.y; }
	friend ostream& operator<< (ostream& os, const Point& p) { return os << "(" << p.x << ", " << p.y << ")"; }

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

constexpr double pi = numbers::pi_v<double>;
constexpr double eps = 1e-5;

void Thephix() {
	Point<double> p;
	array<Point<double>, 4> a {};
	cin >> a[0] >> a[1] >> a[2] >> a[3] >> p;
	
	array<Point<double>, 2> L1, L2;
	if (min(a[0].y, a[1].y) < min(a[2].y, a[3].y)) {
		L1 = { a[0], a[1] };
	} else {
		L1 = { a[2], a[3] };
	}

	if (min(a[01].y, a[2].y) < min(a[3].y, a[0].y)) {
		L2 = { a[1], a[2] };
	} else {
		L2 = { a[3], a[0] };
	}

	int n;
	cin >> n;

	auto f = [&](const array<Point<double>, 2>& line) -> Point<double> {
		Point<double> v = (line[1] - line[0]).rotate(pi / 2);
		v /= v.length();

		double a = abs(v.dot(Point<double> (0, -10)));
		double h = abs((line[1] - p).dot(v));

		if (a < eps || h < eps) {
			return Point<double>  { 0, 0 };
		}

		double T = 2 * sqrt(2 * h / a);
		double t = n - floor(n / T) * T;
		t = min(t, T - t);

		return v * (a * t * t / 2);
	};
	
	p += f(L1) + f(L2);
	cout << p.x << ' ' << p.y << "\n";
}

int main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);
	cout << fixed << setprecision(20);

	int T = 1;
	cin >> T;

	while (T--) {
		Thephix();
	}

	return 0;
}
