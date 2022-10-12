#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;
typedef double db;
const int N = 2010;
const db pi = acos(-1);
const db eps = 1e-8;
int sign(db x) {  
	return fabs(x) < eps ? 0 : (x > eps ? 1 : -1);
}
struct point {
	db x, y;
	db disto(point b) {
		return sqrt((x - b.x) * (x - b.x) + (y - b.y) * (y - b.y));
	}
	db det(point b) {
		return x * b.y - y * b.x;
	}
	point operator - (point b) {
		return (point) {x - b.x, y - b.y};
	}
	bool operator < (const point &b) const {
		return sign(x - b.x) == -1 || (sign(x - b.x) == 0 && sign(y - b.y) == -1);
	}
} a[N], b[N];
int n, top;
db L;
db cross(point a, point b, point c) {
	return (b - a).det(c - a);
}
void convex_hull() {
	sort(a + 1, a + n + 1);
	top = 0;
	for(int i = 1; i <= n; i ++) {
		while(top >= 2 && sign(cross(b[top - 1], b[top], a[i])) == 1) top --;
		b[++ top] = a[i];
	}
	int dfn = top;
	for(int i = n - 1; i >= 1; i --) {
		while(top - dfn >= 1 && sign(cross(b[top - 1], b[top], a[i])) == 1) top --;
		b[++ top] = a[i];
	}
	top --;
}
int main() {
	//freopen("input", "r", stdin);
	while(~ scanf("%d%lf", &n, &L)) {
		db ans = pi * L * 2;
		for(int i = 1; i <= n; i ++) {
			scanf("%lf%lf", &a[i].x, &a[i].y);
		}
		convex_hull();
		for(int i = 1; i <= top; i ++) {
			point &nxt = b[i == top ? 1 : i + 1];
			ans += nxt.disto(b[i]);
		}
		printf("%d\n", (int) (ans + 0.5));
	}
	return 0;
}