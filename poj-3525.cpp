#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;
typedef double db;
const int N = 2010;
const db eps = 1e-9;
struct point {
	db x, y;
	void in_int() { int a, b; scanf("%d%d", &a, &b); x = a; y = b; }
	db det(point b) { return x * b.y - y * b.x; }
	point operator + (const point &b) { return (point) {x + b.x, y + b.y}; }
	point operator - (const point &b) { return (point) {x - b.x, y - b.y}; }
	point operator * (const db &b) { return (point) {x * b, y * b}; }
	void operator += (const point &b) { x += b.x; y += b.y; }
	void operator -= (const point &b) { x -= b.x; y -= b.y; }
	bool operator == (const point &b) { return fabs(x - b.x) < eps && fabs(y - b.y) < eps; }
	db length() { return sqrt(x * x + y * y); }
	point get(db dt) {
		point ans = *this;
		swap(ans.x, ans.y); ans.x *= -1;
		ans = ans * (dt / ans.length());
		return ans;
	}
} t[N], a[N];
int n, c;
struct seg {
	point a, b;
	point vec() { return b - a; }
	db alpha() { return atan2(vec().y, vec().x); }
	bool operator == (seg b) { return vec() == b.vec(); }
} s[N], q[N];
bool cmp(seg x, seg y) {
	db t1 = x.alpha(), t2 = y.alpha();
	if(fabs(t1 - t2) > eps) return t1 < t2;
	return x.vec().det(y.b - x.a) < -eps;
}
point its(seg x, seg y) {
	x.b -= x.a; y.b -= y.a;
	point &a = x.a, &b = x.b, &c = y.a, &d = y.b;
	db k = (a - c).det(d) / d.det(b);
	return a + b * k;
}
bool solve() {
	sort(s + 1, s + c + 1, cmp);
	int l = 0, r = 0;
	for(int i = 1; i <= c; i ++) if(i == 1 || fabs(s[i].alpha() - s[i - 1].alpha()) > eps) {
		while(r - l > 1 && (t[r - 1] - s[i].a).det(s[i].vec()) > eps) r --;
		while(r - l > 1 && (t[l + 1] - s[i].a).det(s[i].vec()) > eps) l ++;
		q[r ++] = s[i];
		if(r - l > 1) t[r - 1] = its(q[r - 1], q[r - 2]);
	}
	while(r - l > 1 && (q[l].b - t[r - 1]).det(q[l].a - t[r - 1]) > eps) r --;
	if(r - l >= 3) {
		t[r] = its(q[l], q[r - 1]); r ++; return true;
	} return false;
}
bool check(db mid) {
	c = n;
	for(int i = 1; i <= n; i ++) {
		int r = i == n ? 1 : i + 1;
		s[i] = (seg) {a[i], a[r]};
		point trans = (s[i].b - s[i].a).get(mid);
		s[i].a += trans; s[i].b += trans;
	}
	return solve();
}
int main() {
	freopen("input", "r", stdin);
	for(int T = 1; T; T ++) {
		scanf("%d", &n);
		if(n == 0) break ;
		for(int i = 1; i <= n; i ++) a[i].in_int();
		solve();
		db l = 0, r = 1e7, mid;
		while(r - l > 1e-7) {
			mid = (l + r) / 2;
			if(check(mid)) l = mid;
			else r = mid;
		}
		printf("%.6f\n", l);
	}
	return 0;
}
//(x, y) -> (-y, x)