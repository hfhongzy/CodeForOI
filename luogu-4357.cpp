#include <algorithm>
#include <cstdio>
#include <queue>
using namespace std;
typedef long long ll;
inline ll sqr(const ll &x) { return x * x; }
const int N = 1e5 + 10;
struct point {
	int x, y;
	ll dto(const point &b) const {
		return sqr(x - b.x) + sqr(y - b.y);
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
ll maxdis(int u, const point &b) {
	if(u == 0) return -1;
	return max(sqr(xl[u] - b.x), sqr(xr[u] - b.x))
	+ max(sqr(yl[u] - b.y), sqr(yr[u] - b.y));
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
int qk, cur;
priority_queue< ll, vector<ll>, greater<ll> > pq;
void query(int l, int r) {
	if(l > r) return ;
	int u = (l + r) >> 1;
	ll d = a[u].dto(a[cur]);
	if(d > pq.top()) { pq.pop(); pq.push(d); }
	ll ld = maxdis(ls[u], a[cur]), rd = maxdis(rs[u], a[cur]);
	if(ld > pq.top() && rd > pq.top()) {
		if(ld > rd) {
			query(l, u - 1);
			if(rd > pq.top()) query(u + 1, r);
		} else {
			query(u + 1, r);
			if(ld > pq.top()) query(l, u - 1);
		}
	} else if(ld > pq.top()) query(l, u - 1);
	else if(rd > pq.top()) query(u + 1, r);
}
int main() {
	scanf("%d%d", &n, &qk); qk <<= 1;
	for(int i = 1; i <= n; i ++) scanf("%d%d", &a[i].x, &a[i].y);
	build(1, n);
	for(int i = 1; i <= qk; i ++) pq.push(0);
	for(cur = 1; cur <= n; cur ++) query(1, n);
	printf("%lld\n", pq.top());
	return 0;
}