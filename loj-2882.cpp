#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;
typedef long long ll;
typedef double db;
const int N = 3005;
const db pi = acos(-1.0);
struct point {
	int x, y, c; db k;
	point(int a = 0, int b = 0) : x(a), y(b) {}
	point operator + (point b) { return point(x + b.x, y + b.y); }
	point operator - (point b) { return point(x - b.x, y - b.y); }
	db dot(point b) { return x * b.x + y * b.y; }
	db det(point b) { return x * b.y - y * b.x; }
	db dis(point b) { return sqrt((x - b.x) * (x - b.x) + (y - b.y) * (y - b.y)); }
	db len() { return sqrt(x * x + y * y); }
	db theta() { return atan2(y, x); }
	bool operator < (const point &b) const {
		return k < b.k;
	}
} a[N], b[N];
int n, bl[N];
ll ans, cnt[2][5];
ll calc(int k, int x) {
	ll res = 1;
	for(int i = 0; i < 3; i ++)
		if(x != i) res *= cnt[k][i];
	return res;
}
void solve(int u) {
	int m = 0;
	for(int i = 1; i <= n; i ++) if(i != u) b[++ m] = a[i];
	for(int i = 1; i <= m; i ++) {
		b[i].x -= a[u].x; b[i].y -= a[u].y;
		b[i].k = b[i].theta();
		if(b[i].k <= 0) b[i].k += pi;
	} 
	memset(cnt, 0, sizeof cnt);
	sort(b + 1, b + m + 1);
	for(int i = 1; i <= m; i ++) {
		if(b[i].y < 0 || (b[i].y == 0 && b[i].x > 0)) {
			bl[i] = 0;
		} else {
			bl[i] = 1;
		}
		cnt[bl[i]][b[i].c] ++;
	}
	for(int i = 1; i <= m; i ++) {
		cnt[bl[i]][b[i].c] --;
		ans += calc(0, b[i].c) * calc(1, a[u].c);
		ans += calc(1, b[i].c) * calc(0, a[u].c);
		cnt[bl[i] ^= 1][b[i].c] ++;
	}
}
int main() {
	//freopen("input", "r", stdin);
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++) {
		scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].c);
	}
	for(int i = 1; i <= n; i ++) solve(i);
	printf("%lld\n", ans >> 2);
	return 0;
}