#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;
typedef double db;
const int N = 16;
const db eps = 1e-9;
int n, I, E, A, x[N], y[N], v[N], l[N];
int sign(db x) {
	return fabs(x) < eps ? 0 : (x > eps ? 1 : -1);
}
struct point {
	db x, y;
	db det(point b) {
		return x * b.y - y * b.x;
	}
	point operator - (const point &b) const {
		return (point) {x - b.x, y - b.y};
	}
	bool operator < (const point &b) const {
		return sign(x - b.x) == -1 || (sign(x - b.x) == 0 && sign(y - b.y) == -1);
	}
	db disto(point b) {
		return sqrt((x - b.x) * (x - b.x) + (y - b.y) * (y - b.y));
	}
} a[N], b[N];
db cross(point a, point b, point c) {
	return (b - a).det(c - a);
}
db convexhull(int S) {
	int m = 0;
	for(int i = 0; i < n; i ++) {
		if(!(S >> i & 1)) {
			a[++ m] = (point) {x[i], y[i]};
		}
	}
	sort(a + 1, a + m + 1);
	if(m <= 1) return 0;
	if(m <= 2) return 2 * a[1].disto(a[2]);
	if(m <= 3) return a[1].disto(a[2]) + a[2].disto(a[3]) + a[3].disto(a[1]);
	int top = 0;
	for(int i = 1; i <= m; i ++) {
		while(top >= 2 && 0 <= sign(cross(b[top - 1], b[top], a[i]))) {
			top --;
		}
		b[++ top] = a[i];
	}
	int dfn = top;
	for(int i = m - 1; i >= 1; i --) {
		while(top >= dfn + 1 && 0 <= sign(cross(b[top - 1], b[top], a[i]))) {
			top --;
		}
		b[++ top] = a[i];
	}
	db dis = 0;
	for(int i = 1; i < top; i ++) {
		dis += b[i].disto(b[i + 1]);
	}
	return dis;
}
int main() {
	freopen("input", "r", stdin);
	int test = 0;
	while(~ scanf("%d", &n) && n) {
		if(test) puts("");
		printf("Forest %d\n", ++ test);
		for(int i = 0; i < n; i ++) {
			scanf("%d%d%d%d", x + i, y + i, v + i, l + i);
		}
		int st = 0, val = 2e9 + 10, cnt = n;
		db extra = 0;
		for(int S = 1; S < (1 << n); S ++) {
			int c = 0, v = 0, l = 0;
			for(int i = 0; i < n; i ++) if(S >> i & 1) {
				c ++; v += ::v[i]; l += ::l[i];
			}
			db ex = l - convexhull(S);
			if(sign(ex) == -1) continue ;
			if(val > v || (val == v && cnt > c)) {
				val = v; cnt = c; extra = ex; st = S;
			}
		}
		printf("Cut these trees:");
		for(int i = 0; i < n; i ++) if(st >> i & 1) {
			printf(" %d", i + 1);
		}
		printf("\nExtra wood: %.2f\n", extra);
	}
	return 0;
}