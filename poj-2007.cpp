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
	int x, y;
} a[N];
int n;
bool cmp(point a, point b) {
	return 1ll * a.x * b.y - 1ll * a.y * b.x > 0;
}
int main() {
	//freopen("input", "r", stdin);
	int x, y;
	while(~ scanf("%d%d", &x, &y)) {
		a[++ n] = (point) {x, y};
	}
	sort(a + 2, a + n + 1, cmp);
	for(int i = 1; i <= n; i ++) {
		printf("(%d,%d)\n", a[i].x, a[i].y);
	}
	return 0;
}