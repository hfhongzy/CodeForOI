#include <algorithm>
#include <cstdio>
#include <set>
using namespace std;
typedef double db;
const int N = 2e5 + 10;
int n, m, st[N];
db p[N], q[N];
struct mat {
	db a[2][2];
	void init(db x1, db x2, db x3, db x4) {
		a[0][0] = x1; a[0][1] = x2; a[1][0] = x3; a[1][1] = x4;
	}
	db * operator [](int x) { return a[x]; }
	mat operator + (mat b) {
		mat ans;
		ans[0][0] = a[0][0] + b[0][0]; ans[0][1] = a[0][1] + b[0][1];
		ans[1][0] = a[1][0] + b[1][0]; ans[1][1] = a[1][1] + b[1][1];
		return ans;
	}
	mat operator * (mat b) {
		mat ans;
		ans.a[0][0] = a[0][0] * b[0][0] + a[0][1] * b[1][0];
		ans.a[0][1] = a[0][0] * b[0][1] + a[0][1] * b[1][1];
		ans.a[1][0] = a[1][0] * b[0][0] + a[1][1] * b[1][0];
		ans.a[1][1] = a[1][0] * b[0][1] + a[1][1] * b[1][1];
		return ans;
	}
};
struct node {
	mat x, y;
	node operator + (const node &b) {
		return (node) {x * b.y + y * b.x, y * b.y};
	}
} t[N << 2];
void build(int u, int l, int r) {
	if(l == r) {
		t[u].y.init(1 - q[l], q[l], 1 - p[l], p[l]);
		t[u].x.init(0, q[l], 0, p[l]);
		return ;
	}
	int mid = (l + r) >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	t[u] = t[u << 1] + t[u << 1 | 1];
}
node query(int u, int l, int r, int ql, int qr) {
	if(l == ql && r == qr) return t[u];
	int mid = (l + r) >> 1;
	if(qr <= mid) return query(u << 1, l, mid, ql, qr);
	if(ql > mid) return query(u << 1 | 1, mid + 1, r, ql, qr);
	return query(u << 1, l, mid, ql, mid) +
	query(u << 1 | 1, mid + 1, r, mid + 1, qr);
}
db qans(int l, int r) {
	node cur = query(1, 1, n + 1, l + 1, r);
	return cur.x[st[l]][st[r]] / cur.y[st[l]][st[r]];
}
int main() {
	scanf("%d%d%*s", &n, &m);
	for(int i = 1; i <= n; i ++) {
		if(i == 1) scanf("%lf", p + i), q[i] = p[i];
		else scanf("%lf%lf", p + i, q + i);
	}
	build(1, 1, n + 1);
	set<int> S; S.insert(0); S.insert(n + 1);
	st[0] = st[n + 1] = 0; db ans = qans(0, n + 1);
	char op[6]; int u, c;
	for(int i = 1; i <= m; i ++) {
		scanf("%s%d", op, &u);
		set<int>::iterator it = S.lower_bound(u), pl = it, pr = it;
		if(*op == 'a') {
			scanf("%d", &c); st[u] = c; pl --;
			ans += - qans(*pl, *pr) + qans(*pl, u) + qans(u, *pr);
			S.insert(u);
		}
		if(*op == 'd') {
			pl --; pr ++;
			ans += - qans(*pl, u) - qans(u, *pr) + qans(*pl, *pr);
			S.erase(it);
		}
		printf("%.6f\n", ans);
	}
	return 0;
}