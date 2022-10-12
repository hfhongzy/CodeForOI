#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;
typedef double db;
const db eps = 1e-18;
const db inf = 2e9;
const int N = 2e4 + 10;
int sign(db x) { return fabs(x) < eps ? 0 : (x > eps ? 1 : -1); }
struct point {
	db x, y;
	void _int() { int a, b; scanf("%d%d", &a, &b); x = a; y = b; }
	point operator + (point b) { return (point) {x + b.x, y + b.y}; }
	point operator - (point b) { return (point) {x - b.x, y - b.y}; }
	point operator * (db b) { return (point) {x * b, y * b}; }
	void operator += (point b) { x += b.x; y += b.y; }
	void operator -= (point b) { x -= b.x; y -= b.y; }
	void operator *= (db b) { x *= b; y *= b; }
	bool operator == (point b) { return !sign(x - b.x) && !sign(y - b.y); }
	db dot(point b) { return x * b.x + y * b.y; }
	db det(point b) { return x * b.y - y * b.x; }
	db length() { return sqrt(x * x + y * y); }
	db disto(point b) { return ((*this) - b).length(); }
	db alpha() { return atan2(y, x); }
} a[N];
db A, B, C;
int n, m, x[N], y[N], z[N];
db f(point a) { return A * a.x + B * a.y + C; }
point its(point a, point b) {
	db u = fabs(f(a)), v = fabs(f(b));
	return (point) {a.x * v + b.x * u, a.y * v + b.y * u} * (1.0 / (u + v));
}
void cutpoly() {
	static point q[N];
	int n = 0; a[m + 1] = a[1];
	for(int i = 1; i <= m; i ++) {
		if(sign(f(a[i])) <= 0) q[++ n] = a[i];
		if(sign(f(a[i])) * sign(f(a[i + 1])) == -1) {
			q[++ n] = its(a[i], a[i + 1]);
		}
	}
	m = n; copy(q + 1, q + m + 1, a + 1);
}
bool solve(int i) {
	m = 0;
	a[++ m] = (point) {0, 0};
	a[++ m] = (point) {inf, 0};
	a[++ m] = (point) {inf, inf};
	a[++ m] = (point) {0, inf};
	const db base = 1;
	for(int j = 1; j <= n; j ++) if(j != i) {
		A = base / x[i] - base / x[j] + base / z[j] - base / z[i];
		B = base / y[i] - base / y[j] + base / z[j] - base / z[i];
		C = base / z[i] - base / z[j];
		if(sign(A) == 0 && sign(B) == 0 && sign(C) >= 0) return 0;
		cutpoly();
	}
	A = B = 1; C = -1;
	cutpoly();
	if(m < 3) return 0;
	db S = 0; a[m + 1] = a[1];
	for(int i = 1; i <= m; i ++) {
		S += a[i].det(a[i + 1]);
	}
	return sign(fabs(S / 2.0)) == 1;
}
int main() {
	//freopen("input", "r", stdin);
	while(~ scanf("%d", &n)) {
		for(int i = 1; i <= n; i ++) {
			scanf("%d%d%d", x + i, y + i, z + i);
		}
		for(int i = 1; i <= n; i ++) {
			puts(solve(i) ? "Yes" : "No");
		}
	}
	return 0;
}
/*
x + y - 10000 < 0;
a (1 / x[i] - 1 / x[j] + 1 / z[j] - 1 / z[i]) + b (1 / y[i] - 1 / y[j] + 1 / z[j] - 1 / z[i]) + 1 / z[i] - 1 / z[j] < 0 (any j) 
*/