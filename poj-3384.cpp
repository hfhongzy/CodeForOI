#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;
typedef double db;
const db eps = 1e-9;
const int N = 210;
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
	db dot(point b) { return x * b.x + y * b.y; }
	db det(point b) { return x * b.y - y * b.x; }
	db length() { return sqrt(x * x + y * y); }
	db disto(point b) { return ((*this) - b).length(); }
	point left_mover(db len) {
		point tr = *this;
		swap(tr.x, tr.y); tr.x *= -1;
		tr *= len / tr.length();
		return tr;
	}	
	db alpha() { return atan2(y, x); }
} a[N];
struct seg {
	point a, b;
	db alpha() { return (b - a).alpha(); }
	void left_move(db len) {
		point trans = (b - a).left_mover(len);
		a += trans; b += trans;
	}
	friend point V(seg x) { return x.b - x.a; }
} e[N];
int n, r;
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
void solve() {
	static seg q[N];
	static point t[N];
	int l = 0, r = 0;
	sort(e + 1, e + n + 1, cmp);
	for(int i = 1; i <= n; i ++) if(i == 1 || sign(e[i].alpha() - e[i - 1].alpha())) {
		while(r - l > 1 && sign((t[r - 1] - e[i].a).det(V(e[i]))) == 1) r --;
		while(r - l > 1 && sign((t[l + 1] - e[i].a).det(V(e[i]))) == 1) l ++;
		q[r ++] = e[i];
		if(r - l > 1) t[r - 1] = its(q[r - 2], q[r - 1]);
	}
	while(r - l > 1 && sign((t[r - 1] - q[l].a).det(V(q[l]))) == 1) r --;
	if(r - l > 2) {
		t[l] = its(q[l], q[r - 1]);
		db dis = -1, x1, y1, x2, y2;
		for(int i = l; i < r; i ++) {
			for(int j = i + 1; j < r; j ++) {
				db d = t[i].disto(t[j]);
				if(d > dis) {
					dis = d; x1 = t[i].x; y1 = t[i].y;
					x2 = t[j].x; y2 = t[j].y;
				}
			}
		}
		printf("%.4f %.4f %.4f %.4f\n", x1, y1, x2, y2);
	}
}
int main() {
	freopen("input", "r", stdin);
	while(~ scanf("%d%d", &n, &r)) {
		for(int i = 1; i <= n; i ++) a[i]._int();
		for(int i = 1; i <= n; i ++) {
			int nxt = i == 1 ? n : i - 1;
			e[i] = (seg) {a[i], a[nxt]};
			e[i].left_move(r);
		}
		solve();
	}
	return 0;
}