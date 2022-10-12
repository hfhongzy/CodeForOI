#include <algorithm>
#include <cctype>
#include <cstdio>
using namespace std;
const int N = 2e5 + 5;
void read(int &x) {
	x = 0; char c = getchar();
	for(; !isdigit(c); c = getchar()) ;
	for(; isdigit(c); c = getchar())
		x = x * 10 + (c & 15);
}
struct point { int x, y, w; } a[N], p[N];
int rt, id, ls[N], rs[N], xl[N], xr[N], yl[N], yr[N];
int sz[N], sum[N], st[N], top, dir[N];
void delnode(int u) { st[++ top] = u; }
int newnode() { return top ? st[top --] : ++ id; }
void upd(int u) {
	xl[u] = xr[u] = a[u].x; yl[u] = yr[u] = a[u].y; sz[u] = 1; sum[u] = a[u].w;
	int son[2] = {ls[u], rs[u]};
	for(int i = 0; i < 2; i ++) if(son[i]) {
		sz[u] += sz[son[i]]; sum[u] += sum[son[i]];
		xl[u] = min(xl[u], xl[son[i]]);
		xr[u] = max(xr[u], xr[son[i]]);
		yl[u] = min(yl[u], yl[son[i]]);
		yr[u] = max(yr[u], yr[son[i]]);
	}
}
int ban, bl, x1, y1, x2, y2, A;
void upd2(int u) {
	sz[u] ++; sum[u] += A;
	xl[u] = min(xl[u], x1);
	xr[u] = max(xr[u], x1);
	yl[u] = min(yl[u], y1);
	yr[u] = max(yr[u], y1);
}
bool cmpx(const point &a, const point &b) { return a.x < b.x; }
bool cmpy(const point &a, const point &b) { return a.y < b.y; }
void rebuild(int &u, int l, int r, point *a) {
	if(l > r) { u = 0; return ; }
	int mid = (l + r) >> 1; u = u == ban ? u : newnode();
	double x = 0, y = 0, zx = 0, zy = 0;
	for(int i = l; i <= r; i ++) { x += a[i].x; y += a[i].y; }
	x /= r - l + 1; y /= r - l + 1;
	for(int i = l; i <= r; i ++) {
		zx += (a[i].x - x) * (a[i].x - x);
		zy += (a[i].y - y) * (a[i].y - y);
	}
	dir[u] = zx > zy ? 0 : 1;
	nth_element(a + l, a + mid, a + r + 1, zx > zy ? cmpx : cmpy);
	rebuild(ls[u], l, mid - 1, a); rebuild(rs[u], mid + 1, r, a);
	::a[u] = a[mid]; upd(u);
}
void insert(int &u) {
	if(u == 0) {
		a[u = newnode()] = (point) {x1, y1, A};
		upd(u); return ;
	}
	int di = dir[u] ? y1 >= a[u].y : x1 >= a[u].x;
	insert(di == 0 ? ls[u] : rs[u]); upd2(u);
	if(max(sz[ls[u]], sz[rs[u]]) > 0.65 * sz[u]) ban = u;
}
void beat(int u) {
	if(u == 0) return ;
	beat(ls[u]); p[++ bl] = a[u]; beat(rs[u]); if(u ^ ban) delnode(u);
}
void rebuild(int u) {
	bl = 0; beat(u); rebuild(u, 1, bl, p);
}
int las;
void query(int u) {
	if(u == 0 || xr[u] < x1 || x2 < xl[u] || yr[u] < y1 || y2 < yl[u]) return ;
	if(x1 <= xl[u] && x2 >= xr[u] && y1 <= yl[u] && y2 >= yr[u]) { las += sum[u]; return ; }
	if(x1 <= a[u].x && x2 >= a[u].x && y1 <= a[u].y && y2 >= a[u].y) las += a[u].w;
	query(ls[u]); query(rs[u]);
}
int main() {
	read(las);
	for(int op; read(op), op != 3; ) {
		if(op == 1) {
			read(x1), read(y1), read(A);
			ban = 0; insert(rt); if(ban) rebuild(ban);
		}
		if(op == 2) {
			read(x1), read(y1), read(x2), read(y2);
			las = 0; query(rt);
			printf("%d\n", las);
		}
	}
	return 0;
}