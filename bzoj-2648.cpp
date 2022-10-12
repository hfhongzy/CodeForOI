#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 1e6 + 10;
struct point {
	int x, y;
	int dto(const point &b) const {
		return abs(x - b.x) + abs(y - b.y);
	}
} a[N], p[N];
int n, q, rt, id, fa[N], ls[N], rs[N], xl[N], xr[N], yl[N], yr[N], sz[N];
bool dir[N];
int st[N], top;
void delnode(int u) { st[++ top] = u; fa[u] = ls[u] = rs[u] = 0; }
int newnode() { return top ? st[top --] : ++ id; }
void upd(int u) {
	xl[u] = xr[u] = a[u].x; yl[u] = yr[u] = a[u].y; sz[u] = 1;
	int son[2] = {ls[u], rs[u]};
	for(int i = 0; i < 2; i ++) if(son[i]) {
		sz[u] += sz[son[i]]; 
		xl[u] = min(xl[u], xl[son[i]]);
		xr[u] = max(xr[u], xr[son[i]]);
		yl[u] = min(yl[u], yl[son[i]]);
		yr[u] = max(yr[u], yr[son[i]]);
	}
}
void upd(int u, const point &b) {
	sz[u] ++;
	xl[u] = min(xl[u], b.x);
	xr[u] = max(xr[u], b.x);
	yl[u] = min(yl[u], b.y);
	yr[u] = max(yr[u], b.y);
}
int mindis(int u, const point &b) {
	int ans = 0;
	if(b.x < xl[u]) ans += xl[u] - b.x;
	if(b.x > xr[u]) ans += b.x - xr[u];
	if(b.y < yl[u]) ans += yl[u] - b.y;
	if(b.y > yr[u]) ans += b.y - yr[u];
	return ans;
}
bool cmpx(const point &a, const point &b) { return a.x < b.x; }
bool cmpy(const point &a, const point &b) { return a.y < b.y; }
int build(int l, int r, point *a) {
	if(l > r) return 0;
	int mid = (l + r) >> 1, u = newnode();
	double x = 0, y = 0, zx = 0, zy = 0;
	for(int i = l; i <= r; i ++) { x += a[i].x; y += a[i].y; }
	x /= r - l + 1; y /= r - l + 1;
	for(int i = l; i <= r; i ++) {
		zx += (a[i].x - x) * (a[i].x - x);
		zy += (a[i].y - y) * (a[i].y - y);
	}
	dir[u] = zx > zy ? 0 : 1;
	nth_element(a + l, a + mid, a + r + 1, zx > zy ? cmpx : cmpy);
	ls[u] = build(l, mid - 1, a); rs[u] = build(mid + 1, r, a);
	if(ls[u]) fa[ls[u]] = u; if(rs[u]) fa[rs[u]] = u;
	::a[u] = a[mid]; upd(u); return u;
}
point cur;
int ans, ban, f, bl;
void insert(int &u) {
	if(u == 0) {
		a[u = newnode()] = cur; fa[u] = f;
		upd(u); return ;
	}
	int di = dir[u] ? cur.y >= a[u].y : cur.x >= a[u].x;
	f = u; insert(di == 0 ? ls[u] : rs[u]); upd(u, cur);
	if(max(sz[ls[u]], sz[rs[u]]) > 0.8 * sz[u]) ban = u;
}
void beat(int u) {
	if(u == 0) return ;
	beat(ls[u]); p[++ bl] = a[u]; beat(rs[u]); delnode(u);
}
void rebuild(int u) {
	if(u == 0) return ;
	int ff = fa[u], &v = ff ? (ls[ff] == u ? ls[ff] : rs[ff]) : rt;
	bl = 0; beat(u); v = build(1, bl, p); fa[v] = ff;
}
void query(int u) {
	if(u == 0) return ;
	int d = a[u].dto(cur);
	if(d < ans) ans = d;
	int ld = mindis(ls[u], cur), rd = mindis(rs[u], cur);
	if(ld < ans && rd < ans) {
		if(ld < rd) {
			query(ls[u]);
			if(rd < ans) query(rs[u]);
		} else {
			query(rs[u]);
			if(ld < ans) query(ls[u]);
		}
	} else if(ld < ans) query(ls[u]);
	else if(rd < ans) query(rs[u]);
}
int main() {
	// freopen("input", "r", stdin);
	scanf("%d%d", &n, &q);
	for(int i = 1; i <= n; i ++) scanf("%d%d", &p[i].x, &p[i].y);
	rt = build(1, n, p);
	for(int op, i = 1; i <= q; i ++) {
		scanf("%d%d%d", &op, &cur.x, &cur.y);
		if(op == 1) { ban = 0; insert(rt); rebuild(ban); }
		if(op == 2) { ans = 2e8; query(rt); printf("%d\n", ans); }
	}
	return 0;
}