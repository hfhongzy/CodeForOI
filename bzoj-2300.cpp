#include <algorithm>
#include <cstdio>
#include <cmath>
#include <set>
using namespace std;
typedef double db;
const db eps = 1e-8;
const int N = 3e5 + 10;
struct point {
	int x, y;
	point operator - (const point &b) const { return (point) {x - b.x, y - b.y}; }
	db disto(const point &b) const {
		return sqrt((x - b.x) * (x - b.x) + (y - b.y) * (y - b.y));
	}
	int det(point b) { return x * b.y - y * b.x; }
	bool operator < (const point &b) const {
		return x < b.x || (x == b.x && y < b.y);
	}
} a[N];
int q, z, x, y, n;
struct opt { int op, x; } b[N];
db ans[N], res;
set<point> S;
void insert(point p) {
	set<point>::iterator pre, nxt, t;
	nxt = S.lower_bound(p); pre = nxt; pre --;
	if((p - *pre).det(*nxt - *pre) >= 0) return ;
	S.insert(p); res -= pre -> disto(*nxt);
	res += pre -> disto(p) + nxt -> disto(p);
	while(1) {
		t = nxt; t ++;
		if(t == S.end()) break ;
		if((*nxt - p).det(*t - *nxt) < 0) break ;
		S.erase(nxt); res -= nxt -> disto(p) + nxt -> disto(*t);
		nxt = t; res += nxt -> disto(p);
	}
	while(1) {
		t = pre;
		if(t == S.begin()) break ;
		t --;
		if((*pre - *t).det(p - *pre) < 0) break ;
		S.erase(pre); res -= pre -> disto(p) + pre -> disto(*t);
		pre = t; res += pre -> disto(p);
	} 
}
int main() {
	freopen("input", "r", stdin);
	static bool use[N];
	scanf("%d%d%d%d", &z, &x, &y, &n);
	for(int i = 1; i <= n; i ++) {
		scanf("%d%d", &a[i].x, &a[i].y);
	}
	scanf("%d", &q);
	for(int i = 1; i <= q; i ++) {
		scanf("%d", &b[i].op);
		if(b[i].op == 1) {
			scanf("%d", &b[i].x);
			use[b[i].x] = 1;
		}
	}
	for(int i = 1; i <= n; i ++) if(!use[i]) b[++ q] = (opt) {1, i};
	S.insert((point) {0, 0}); S.insert((point) {z, 0}); S.insert((point) {x, y});
	res = (point) {x, y}.disto((point) {0, 0}) + (point) {x, y}.disto((point) {z, 0});
	for(int i = q; i >= 1; i --) {
		if(b[i].op == 1) { ans[i] = -1; insert(a[b[i].x]); } else ans[i] = res;
	}
	for(int i = 1; i <= q; i ++) if(ans[i] >= 0) printf("%.2f\n", ans[i]);
	return 0;
}