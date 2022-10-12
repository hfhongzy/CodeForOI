#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;
typedef double db;
const int N = 2010;
const db eps = 1e-9;
int n, top;
int sign(db x) {
	return fabs(x) < eps ? 0 : (x > eps ? 1 : -1);
}
struct point {
	db x, y;
	db det(point b) { return x * b.y - y * b.x; }
	db dot(point b) { return x * b.x + y * b.y; }
	point operator - (const point &b) const {
		return (point) {x - b.x, y - b.y};
	}
	bool operator < (const point &b) const {
		return sign(x - b.x) == -1 || (sign(x - b.x) == 0 && sign(y - b.y) == -1);
	}
	bool operator != (const point &b) const {
		return sign(x - b.x) != 0 || sign(y - b.y) != 0;
	}
	db disto(point b) {
		return sqrt((x - b.x) * (x - b.x) + (y - b.y) * (y - b.y));
	}
} a[N], b[N];
db cross(point a, point b, point c) {
	return (b - a).det(c - a);
}
void convexhull() {
	sort(a + 1, a + n + 1);
	if(n < 3) {
		copy(a + 1, a + n + 1, b + 1);
		top = n; return ;
	}
	top = 0;
	for(int i = 1; i <= n; i ++) {
		while(top >= 2 && 0 <= sign(cross(b[top - 1], b[top], a[i]))) {
			top --;
		}
		b[++ top] = a[i];
	}
	int dfn = top;
	for(int i = n - 1; i >= 1; i --) {
		while(top >= dfn + 1 && 0 <= sign(cross(b[top - 1], b[top], a[i]))) {
			top --;
		}
		b[++ top] = a[i];
	}
	top --;
}
int main() {
	freopen("input", "r", stdin);
	while(~ scanf("%d", &n)) {
		for(int i = 1; i <= n; i ++) scanf("%lf%lf", &a[i].x, &a[i].y);
		convexhull(); db s = 0;
		for(int i = 1; i <= top; i ++) {
			int r = i == top ? 1 : i + 1;
			s += b[r].det(b[i]) / 2;
		}
		printf("%d\n", (int) (s / 50));
	}
	return 0;
}