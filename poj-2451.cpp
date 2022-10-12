#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;
typedef double db;
const db eps = 1e-8;
const int N = 4e4 + 10;
int sign(db x) { return fabs(x) < eps ? 0 : (x > eps ? 1 : -1); }
struct point {
	db x, y;
	void _db() { scanf("%lf%lf", &x, &y); }
	point operator + (point b) { return (point) {x + b.x, y + b.y}; }
	point operator - (point b) { return (point) {x - b.x, y - b.y}; }
	point operator * (db b) { return (point) {x * b, y * b}; }
	void operator += (point b) { x += b.x; y += b.y; }
	void operator -= (point b) { x -= b.x; y -= b.y; }
	void operator *= (db b) { x *= b; y *= b; }
	db dot(point b) { return x * b.x + y * b.y; }
	db det(point b) { return x * b.y - y * b.x; }
	db length() { return sqrt(x * x + y * y); }
	db disto(point b) { return ((*this) - b).length(); }
	db alpha() { return atan2(y, x); }
	void rev() { swap(x, y); x *= -1; }
} a[N];
struct seg {
	point a, b;
	db alpha() { return (b - a).alpha(); }
	friend point V(seg x) { return x.b - x.a; }
} e[N];
int n, c;
bool cmp(seg a, seg b) {
	db k1 = a.alpha(), k2 = b.alpha();
	if(fabs(k1 - k2) > eps) return k1 < k2;
	return sign(V(b).det(a.a - b.a)) == 1;
}
point its(seg l1, seg l2) {
	point &a = l1.a, &b = l1.b, &c = l2.a, &d = l2.b;
	b -= a; d -= c;
	db k1 = (c.det(d) - a.det(d)) / b.det(d);
	return a + b * k1;
}
db solve() {
	static seg q[N];
	static point t[N];
	int l = 0, r = 0;
	sort(e + 1, e + c + 1, cmp);
	for(int i = 1; i <= c; i ++) if(i == 1 || sign(e[i].alpha() - e[i - 1].alpha())) {
		while(r - l > 1 && sign((t[r - 1] - e[i].a).det(V(e[i]))) == 1) r --;
		while(r - l > 1 && sign((t[l + 1] - e[i].a).det(V(e[i]))) == 1) l ++;
		q[r ++] = e[i];
		if(r - l > 1) t[r - 1] = its(q[r - 2], q[r - 1]);
	}
	while(r - l > 1 && sign((t[r - 1] - q[l].a).det(V(q[l]))) == 1) r --;
	t[l] = its(q[l], q[r - 1]);
	db ans = 0;
	for(int i = l; i < r; i ++) {
		int nxt = i == r - 1 ? l : i + 1;
		ans += t[i].det(t[nxt]);
	}
	return fabs(ans / 2);
}
void add(db x1, db y1, db x2, db y2, bool tag) {
	//tag = 0: (x1, y1) is closer
	if(tag) { swap(x1, x2); swap(y1, y2); }
	seg t = (seg) {(point) {x1, y1}, (point) {x2, y2}};
	point mid = t.a + ( (t.b - t.a) * 0.5 );
	point dir = t.b - mid; dir.rev();
	e[++ c] = (seg) {mid, mid + dir};
	//printf("(%f, %f) -> (%f, %f)\n", e[c].a.x, e[c].a.y, e[c].b.x, e[c].b.y);
}
int main() {
	freopen("input", "r", stdin);
	db x, y, lx = 0, ly = 0;
	while(~ scanf("%d", &n)) {
		c = 0;
		for(int i = 1; i <= n; i ++) {
			scanf("%lf%lf%lf%lf", &x, &y, &lx, &ly);
			e[++ c] = (seg) {(point) {x, y}, (point) {lx, ly}};
		}
		e[++ c] = (seg) {(point) {0, 0}, (point) {10000, 0}};
		e[++ c] = (seg) {(point) {10000, 0}, (point) {10000, 10000}};
		e[++ c] = (seg) {(point) {10000, 10000}, (point) {0, 10000}};
		e[++ c] = (seg) {(point) {0, 10000}, (point) {0, 0}};
		printf("%.1f\n", solve());
	}
	return 0;
}