#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
typedef double db;
const int N = 1e5 + 10;
const db eps = 1e-10;
struct node {
	db a, b, r, x, y; int id;
} t[N], px[N];
int n;
db f[N];
bool cmpx(node r1, node r2) { return r1.x - r2.x < -eps; }
bool cmpk(node r1, node r2) { return r1.a * r2.b - r2.a * r1.b > eps; }
bool judge(node r1, node r2, node r3) {
	db x1 = r2.x - r1.x, y1 = r2.y - r1.y;
	db x2 = r3.x - r1.x, y2 = r3.y - r1.y;
	return x1 * y2 - y1 * x2 > -eps;
}
db calc(node u, node v) {
	return u.a * v.x + u.b * v.y;
}
void solve(int l, int r) {
	if(l == r) {
		f[l] = max(f[l], f[l - 1]);
		t[l].y = f[l] / (t[l].r * t[l].a + t[l].b);
		t[l].x = t[l].r * t[l].y;
		px[l] = t[l];
		return ;
	}
	int mid = (l + r) >> 1;
	static node tmp[N];
	int tp = l;
	for(int i = l; i <= r; i ++)
		if(t[i].id <= mid) tmp[tp ++] = t[i];
	for(int i = l; i <= r; i ++)
		if(t[i].id > mid) tmp[tp ++] = t[i];
	copy(tmp + l, tmp + r + 1, t + l);

	solve(l, mid);

	static node q[N];
	int ql = 0, qr = 0;
	for(int i = l; i <= mid; i ++) {
		while(qr - ql > 1 && judge(q[qr - 2], q[qr - 1], px[i])) qr --;
		q[qr ++] = px[i];
	}
	for(int i = r; i > mid; i --) {
		node j = t[i];
		while(qr - ql > 1 && calc(j, q[ql]) - calc(j, q[ql + 1]) < eps) ql ++;
		f[j.id] = max(f[j.id], calc(j, q[ql]));
	}

	solve(mid + 1, r);

	int t1 = l, t2 = mid + 1;
	for(int i = l; i <= r; i ++) {
		if(t2 > r || (t1 <= mid && cmpx(px[t1], px[t2]))) {
			tmp[i] = px[t1 ++];
		} else {
			tmp[i] = px[t2 ++];
		}
	}
	copy(tmp + l, tmp + r + 1, px + l);
}
int main() {
	freopen("input", "r", stdin);
	scanf("%d%lf", &n, f);
	for(int i = 1; i <= n; i ++) {
		scanf("%lf%lf%lf", &t[i].a, &t[i].b, &t[i].r);
		t[i].id = i;
	}
	sort(t + 1, t + n + 1, cmpk);
	solve(1, n);
	printf("%.3lf\n", f[n]);
	return 0;
}