#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 1e5 + 10;
struct point {
	int x, y;
	int dto(const point &b) const {
		return abs(x - b.x) + abs(y - b.y);
	}
} a[N];
int n, ls[N], rs[N], xl[N], xr[N], yl[N], yr[N];
bool cmpx(const point &a, const point &b) { return a.x < b.x; }
bool cmpy(const point &a, const point &b) { return a.y < b.y; }
void upd(int u) {
	xl[u] = xr[u] = a[u].x; yl[u] = yr[u] = a[u].y;
	if(ls[u]) {
		xl[u] = min(xl[u], xl[ls[u]]);
		xr[u] = max(xr[u], xr[ls[u]]);
		yl[u] = min(yl[u], yl[ls[u]]);
		yr[u] = max(yr[u], yr[ls[u]]);
	}
	if(rs[u]) {
		xl[u] = min(xl[u], xl[rs[u]]);
		xr[u] = max(xr[u], xr[rs[u]]);
		yl[u] = min(yl[u], yl[rs[u]]);
		yr[u] = max(yr[u], yr[rs[u]]);
	}
}
int mindis(int u, const point &b) {
	int ans = 0;
	if(b.x < xl[u]) ans += xl[u] - b.x;
	if(b.x > xr[u]) ans += b.x - xr[u];
	if(b.y < yl[u]) ans += yl[u] - b.y;
	if(b.y > yr[u]) ans += b.y - yr[u];
	return ans;
}
int maxdis(int u, const point &b) {
	return max(abs(xl[u] - b.x), abs(xr[u] - b.x)) + max(abs(yl[u] - b.y), abs(yr[u] - b.y));
}

int build(int l, int r) {
	if(l > r) return 0;
	int u = (l + r) >> 1;
	double x = 0, y = 0, zx = 0, zy = 0;
	for(int i = l; i <= r; i ++) {
		x += a[i].x; y += a[i].y;
	}
	x /= r - l + 1; y /= r - l + 1;
	for(int i = l; i <= r; i ++) {
		zx += (a[i].x - x) * (a[i].x - x);
		zy += (a[i].y - y) * (a[i].y - y);
	}
	nth_element(a + l, a + u, a + r + 1, zx > zy ? cmpx : cmpy);
	ls[u] = build(l, u - 1); rs[u] = build(u + 1, r);
	upd(u); return u;
}
int cur, ans;
void querymax(int l, int r) {
	if(l > r) return ;
	int u = (l + r) >> 1, d = a[u].dto(a[cur]);
	if(u != cur && d > ans) ans = d;
	int ld = maxdis(ls[u], a[cur]), rd = maxdis(rs[u], a[cur]);
	if(ld > ans && rd > ans) {
		if(ld > rd) {
			querymax(l, u - 1);
			if(rd > ans) querymax(u + 1, r);
		} else {
			querymax(u + 1, r);
			if(ld > ans) querymax(l, u - 1);
		}
	} else if(ld > ans) querymax(l, u - 1);
	else if(rd > ans) querymax(u + 1, r);
}
void querymin(int l, int r) {
	if(l > r) return ;
	int u = (l + r) >> 1, d = a[u].dto(a[cur]);
	if(u != cur && d < ans) ans = d;
	int ld = mindis(ls[u], a[cur]), rd = mindis(rs[u], a[cur]);
	if(ld < ans && rd < ans) {
		if(ld < rd) {
			querymin(l, u - 1);
			if(rd < ans) querymin(u + 1, r);
		} else {
			querymin(u + 1, r);
			if(ld < ans) querymin(l, u - 1);
		}
	} else if(ld < ans) querymin(l, u - 1);
	else if(rd < ans) querymin(u + 1, r);
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++) scanf("%d%d", &a[i].x, &a[i].y);
	build(1, n);
	int res = 2e9 + 10;
	for(cur = 1; cur <= n; cur ++) {
		ans = 2e9; querymin(1, n); int now = - ans;
		ans = 0; querymax(1, n); now += ans;
		res = min(res, now);
	}
	printf("%d\n", res);
	return 0;
}