#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;
typedef double db;
const int N = 1010;
const db eps = 1e-8;
int sign(db x) {  
	return fabs(x) < eps ? 0 : (x > eps ? 1 : -1);
}
struct line {
	db l, r, y;
	void in() { scanf("%lf%lf%lf", &l, &r, &y); }
	bool end() { return sign(l) == 0 && sign(r) == 0 && sign(y) == 0; }
} a[N], A, B;
int n, nn;
struct node {
	db l, r;
	bool operator < (const node &b) const {
		return sign(l - b.l) == -1 || (sign(l - b.l) == 0 && sign(r - b.r) == -1);
	}
} b[N];
struct point {
	db x, y;
	point(db a = 0, db b = 0) : x(a), y(b) {}
	point operator + (point b) { return point(x + b.x, y + b.y); }
	point operator - (point b) { return point(x - b.x, y - b.y); }
	point operator * (db b) { return point(x * b, y * b); }
	point operator / (db b) { return point(x / b, y / b); }
	db dot(point b) { return x * b.x + y * b.y; }
	db det(point b) { return x * b.y - y * b.x; }
	db dis(point b) { return sqrt((x - b.x) * (x - b.x) + (y - b.y) * (y - b.y)); }
	db len() { return sqrt(x * x + y * y); }
};
db get(db x1, db y1, db x2, db y2) {
	if(fabs(x1 - x2) < eps) return x1;
	db k = (y1 - y2) / (x1 - x2);
	db b0 = y1 - k * x1;
	return (B.y - b0) / k;
}
int main() {
	//freopen("input", "r", stdin);
	while(A.in(), !A.end()) {
		B.in(); scanf("%d", &n); nn = 0;
		for(int i = 1; i <= n; i ++) a[i].in();
		for(int i = 1; i <= n; i ++) if(sign(a[i].y - A.y) == -1 && sign(a[i].y - B.y) == 1) {
			db l = get(A.r, A.y, a[i].l, a[i].y);
			db r = get(A.l, A.y, a[i].r, a[i].y);
			b[++ nn] = (node) {max(l, B.l), min(r, B.r)};
			if(~ sign(b[nn].l - b[nn].r)) nn --;
		}
		if(nn == 0) {
			printf("%.2f\n", B.r - B.l);
			continue ;
		}
		sort(b + 1, b + nn + 1);
		db maxr = B.l, ans = 0;
		for(int i = 1; i <= nn; i ++) {
			ans = max(ans, b[i].l - maxr);
			maxr = max(maxr, b[i].r);
		}
		ans = max(ans, B.r - maxr);
		if(!sign(ans)) puts("No View");
		else printf("%.2f\n", ans);
	}
	return 0;
}