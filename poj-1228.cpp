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
bool onseg(point a, point b, point o) {
	return !sign(cross(a, b, o)) && sign((a - o).dot(b - o)) <= 0;
}
int main() {
	int test; scanf("%d", &test);
	while(test --) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i ++) scanf("%lf%lf", &a[i].x, &a[i].y);
		convexhull(); bool tag = top >= 3 && n >= 6;
		for(int i = 1; i <= top; i ++) if(tag) {
			int r = i == top ? 1 : i + 1, cnt = 0;
			for(int j = 1; j <= n; j ++) {
				if(a[j] != b[i] && a[j] != b[r] && onseg(b[i], b[r], a[j])) {
					cnt = 1; break ;
				}
			}
			if(cnt == 0) {
				tag = 0;
			}
		}
		puts(tag ? "YES" : "NO");
	}
	return 0;
}