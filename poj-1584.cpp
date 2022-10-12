#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;
typedef double db;
const int N = 210;
const db eps = 1e-12;
int sign(db x) {
	return fabs(x) < eps ? 0 : (x > eps ? 1 : -1);
}
struct point {
	db x, y;
	point(db a = 0, db b = 0) : x(a), y(b) {}
	point operator + (point b) { return point(x + b.x, y + b.y); }
	point operator - (point b) { return point(x - b.x, y - b.y); }
	db dot(point b) { return x * b.x + y * b.y; }
	db det(point b) { return x * b.y - y * b.x; }
	db dis(point b) { return sqrt((x - b.x) * (x - b.x) + (y - b.y) * (y - b.y)); }
	db len() { return sqrt(x * x + y * y); }
} a[N], o;
int n;
point vec(point a, point b) { return b - a; }
db disto(point x, point y, point o) {
	if(vec(x, y).dot(vec(x, o)) < -eps) {
		return min(x.dis(o), y.dis(o));
	}
	return fabs(vec(x, y).det(vec(x, o))) / vec(x, y).len();
}
int main() {
	//freopen("input", "r", stdin);
	while(~ scanf("%d", &n)) {
		if(n < 3) break ; db R; scanf("%lf%lf%lf", &R, &o.x, &o.y);
		for(int i = 0; i < n; i ++) scanf("%lf%lf", &a[i].x, &a[i].y);
		bool vis[3] = {0}, convex = 1;
		for(int i = 0; i < n; i ++) {
			point &l = a[i == 0 ? n - 1 : i - 1];
			point &r = a[i == n - 1 ? 0 : i + 1];
			vis[1 + sign(vec(a[i], l).det(vec(a[i], r)))] = 1;
			if(vis[0] & vis[2]) {
				convex = 0; break ;
			}
		}
		if(!convex) puts("HOLE IS ILL-FORMED");
		else {
			bool tag = 1, vis2[3] = {0};
			for(int i = 0; i < n; i ++) {
				point &r = a[i == n - 1 ? 0 : i + 1];
				vis2[1 + sign(vec(a[i], o).det(vec(a[i], r)))] = 1;
				if(vis2[1] || (vis2[0] & vis2[2])) {
					tag = 0; break ;
				}
				if(disto(a[i], r, o) - R < -eps) {
					tag = 0; break ;
				}
			}
			puts(tag ? "PEG WILL FIT" : "PEG WILL NOT FIT");
		}
	}
	return 0;
}