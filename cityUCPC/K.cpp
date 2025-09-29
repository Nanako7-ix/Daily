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
	auto operator<=>(const Point& o) const = default;
	
	friend istream& operator>> (istream& is, Point& p) { return is >> p.x >> p.y; }
	friend ostream& operator<< (ostream& os, const Point& p) { return os << "(" << p.x << ", " << p.y << ")"; }

	T square() const { return dot(*this); }
};

using point = Point<f64>;

constexpr f64 eps = 0;
constexpr f64 PI = std::numbers::pi_v<f64>;

void Thephix() {
	f64 a, b, x1, y1, x2, y2;
	cin >> a >> b >> x1 >> y1 >> x2 >> y2;

	point p1(x1 / a, y1 / b), p2(x2 / a, y2 / b);

	f64 h = abs(p1.cross(p2)) / sqrtl((p1 - p2).square());

	if (h > 1 - eps) {
		cout << "-1\n";
		return;
	}

	f64 angle = acosl(h) * 2;
	f64 S1 = PI * angle / (2 * PI) - sinl(angle) / 2;
	f64 S2 = PI - S1;
	cout << fixed << setprecision(20) << S1 / S2 << endl;
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
