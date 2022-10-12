#include <algorithm>
#include <cstdio>
using namespace std;
typedef double db;
const int N = 2e5 + 10;
struct Node {
	db x, l, r; int op;
	bool operator < (const Node &b) const {
		return x < b.x || (x == b.x && op > b.op);
	}
} a[N];
int n, m;
db b[N], tag[N << 2], s[N << 2];
void pu(int u, int l, int r) {
	s[u] = tag[u] >= 1 ? b[r + 1] - b[l] : (l == r ? 0 : s[u << 1] + s[u << 1 | 1]); 
}
void modify(int u, int l, int r, int ql, int qr, int v) {
	if(l == ql && r == qr) { tag[u] += v; pu(u, l, r); return ; }
	int mid = (l + r) >> 1;
	if(qr <= mid) modify(u << 1, l, mid, ql, qr, v);
	else if(ql > mid) modify(u << 1 | 1, mid + 1, r, ql, qr, v);
	else {
		modify(u << 1, l, mid, ql, mid, v);
		modify(u << 1 | 1, mid + 1, r, mid + 1, qr, v);
	}
	pu(u, l, r);
}
int main() {
	freopen("input", "r", stdin);
	int cas = 1;
	while(scanf("%d", &n) && n) {
		db x1, y1, x2, y2;
		for(int i = 1; i <= n; i ++) {
			scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
			b[i * 2 - 1] = y1; b[i * 2] = y2;
			a[i * 2 - 1] = (Node) {x1, y1, y2, 1};
			a[i * 2] = (Node) {x2, y1, y2, -1};
		}
		sort(b + 1, b + 2 * n + 1);
		m = unique(b + 1, b + 2 * n + 1) - b - 1;
		for(int i = 1; i < 2 * n; i += 2) {
			a[i].l = a[i + 1].l = lower_bound(b + 1, b + m + 1, a[i].l) - b;
			a[i].r = a[i + 1].r = lower_bound(b + 1, b + m + 1, a[i].r) - b;
		}
		sort(a + 1, a + 2 * n + 1);
		db ans = 0; a[0].x = a[1].x;
		for(int i = 1; i <= 2 * n; i ++) {
			if(a[i].x != a[i - 1].x) ans += (a[i].x - a[i - 1].x) * s[1]; 
			modify(1, 1, m, a[i].l, a[i].r - 1, a[i].op);
		}
		printf("Test case #%d\n", cas ++);
		printf("Total explored area: %.2f\n\n", ans);
	}
	return 0;
}