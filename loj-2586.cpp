#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cmath>
using namespace std;
typedef double db;
const int N = 3e5 + 10;
const db pi = acos(-1), eps = 1e-3;
struct point { db x, y, r; } p[N];
int n, ans[N], ch[N][2];
db rgx[N][2], rgy[N][2];
struct kdt {
	int id; db x[2], y[2]; int r;
	bool operator < (const kdt &b) const {
		return r > b.r || r == b.r && id < b.id;
	}
} a[N], b[N];
bool cmpx(kdt a, kdt b) { return p[a.id].x + eps < p[b.id].x; }
bool cmpy(kdt a, kdt b) { return p[a.id].y + eps < p[b.id].y; }
int build(int l, int r, int d = 0) {
	if(l > r) return 0;
	int u = (l + r) >> 1, t = 0;
	nth_element(b + l, b + u, b + r + 1, d ? cmpx : cmpy);
	rgx[u][0] = b[u].x[0]; rgx[u][1] = b[u].x[1];
	rgy[u][0] = b[u].y[0]; rgy[u][1] = b[u].y[1];
	if(l < r) {
		ch[u][0] = build(l, u - 1, d ^ 1);
		ch[u][1] = build(u + 1, r, d ^ 1);
		if(t = ch[u][0]) {
			rgx[u][0] = min(rgx[u][0], rgx[t][0]);
			rgx[u][1] = max(rgx[u][1], rgx[t][1]);
			rgy[u][0] = min(rgy[u][0], rgy[t][0]);
			rgy[u][1] = max(rgy[u][1], rgy[t][1]);
		}
		if(t = ch[u][1]) {
			rgx[u][0] = min(rgx[u][0], rgx[t][0]);
			rgx[u][1] = max(rgx[u][1], rgx[t][1]);
			rgy[u][0] = min(rgy[u][0], rgy[t][0]);
			rgy[u][1] = max(rgy[u][1], rgy[t][1]);
		}
	}
	return u;
}
bool ins(int a, int b) {
	return (p[a].x - p[b].x) * (p[a].x - p[b].x) + (p[a].y - p[b].y) * (p[a].y - p[b].y)
	<= (p[a].r + p[b].r) * (p[a].r + p[b].r) + eps;
}
void modify(int u, int cur) {
	if(!u) return ;
	if(a[cur].x[0] > rgx[u][1] + eps || a[cur].x[1] < rgx[u][0] - eps) return ;
	if(a[cur].y[0] > rgy[u][1] + eps || a[cur].y[1] < rgy[u][0] - eps) return ;
	if(!ans[b[u].id] && ins(b[u].id, a[cur].id)) ans[b[u].id] = a[cur].id;
	modify(ch[u][0], cur); modify(ch[u][1], cur);
}
int main() {
	srand(time(0));
	scanf("%d", &n);
	db t = pi / 2 * (rand() % 2000 + 1) / 2001.0;
	// printf("%f %f %f %f %f\n", a[0].id, a[0].x[0], a[0].x[1], a[0].y[0], a[0].y[1], a[0].r);
	for(int i = 1; i <= n; i ++) {
		int x, y, r; scanf("%d%d%d", &x, &y, &r);
		p[i] = (point) {x * cos(t) + y * sin(t), - x * sin(t) + y * cos(t), (db) r};
		a[i].id = i; a[i].x[0] = p[i].x - r; a[i].x[1] = p[i].x + r;
		a[i].y[0] = p[i].y - r; a[i].y[1] = p[i].y + r; a[i].r = r;
	}
	sort(a + 1, a + n + 1); copy(a + 1, a + n + 1, b + 1);
	int rt = build(1, n);
	for(int i = 1; i <= n; i ++)
		if(!ans[a[i].id]) modify(rt, i);
	for(int i = 1; i <= n; i ++)
		printf("%d%c", ans[i], " \n"[i == n]);
	return 0;
}