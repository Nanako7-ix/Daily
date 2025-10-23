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

template<typename T, typename Iter>
bool point_in_polygon(const Point<T>& p, const Iter& l, const Iter& r) {
	int n = r - l;
	for (int i = 0; i < n; ++i) {
		Point<T> u = l[i], v = l[(i + 1) % n];
		if (
			(p - u).cross(p - v) == 0 &&
			std::min(u.x, v.x) <= p.x && p.x <= std::max(u.x, v.x) &&
			std::min(u.y, v.y) <= p.y && p.y <= std::max(u.y, v.y)
		) return true;
	}

	bool ret = false;
	for (int i = 0; i < n; ++i) {
		Point<T> u = l[i], v = l[(i + 1) % n];
		if (u.x < p.x && p.x <= v.x && (p - v).corss(u - v) > 0) {
			ret ^= 1;
		}
		if (v.x < p.x && p.x <= u.x && (p - u).cross(v - u) > 0) {
			ret ^= 1;
		}
	}

	return ret;
}

template<typename T>
double distancePS(const Point<T> &p, const Point<T> &u, const Point<T>& v) {
	if (dot(p - u, v - u) < 0) return (p - u).length();
	if (dot(p - v, u - v) < 0) return (p - v).length();
	return abs((p - u).cross(p - v)) / (u - v).length();
}

constexpr double pi = numbers::pi_v<double>;

void Thephix() {
	int n, d;
	double t;
	Point<i64> p;
	cin >> n >> p.x >> p.y >> d >> t;

	vector<Point<i64>> a(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i].x >> a[i].y;
	}

	int k = t / (2 * pi) + 0.5;
	t -= 2 * k * pi;
	if (t < 0) t += 2 * pi, k--;
	
	vector<double> b;
	for (int i = 0; i < n; ++i) {
		b.push_back(atan2(a[i].y, a[i].x) - asin(d / a[i].length()));
		b.push_back(atan2(a[i].y, a[i].x) + asin(d / a[i].length()));
	}

	double Min = *min_element(b.begin(), b.end());
	for (auto& x : b) {
		if (x - Min > pi) {
			x -= 2 * pi;
		}
	}

	Min = *min_element(b.begin(), b.end());
	double Max = *max_element(b.begin(), b.end());
	
	double ans = (Max - Min) * k;

	double angle = atan2(p.y, p.x);
	while (angle > Min) angle -= 2 * pi;

	while (angle < Max) {
		double x = angle, y = angle + t;
		double l = max(x, Min), r = min(y, Max);
		if (l < r) ans += r - l;
		angle += 2 * pi;
	}

	cout << ans << "\n";
}

int main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	cout << fixed << setprecision(20);

	int T = 1;
	// cin >> T;

	while (T--) {
		Thephix();
	}

	return 0;
}
