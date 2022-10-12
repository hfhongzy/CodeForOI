#include <algorithm>
#include <cstdio>
using namespace std;
typedef double db;
const int N = 1e5 + 10;
const db INF = 1e18;
int gcd(int x, int y) {
	return y == 0 ? x : gcd(y, x % y);
}
struct fac {
	int x, y;
	void work() {
		int g = gcd(x, y); x /= g; y /= g;
	}
	fac(int xx = 0, int yy = 1) {
		x = xx; y = yy; work();
	}
	bool operator < (const fac &b) const {
		return 1ll * x * b.y < 1ll * b.x * y;
	}
};
struct node {
	int d, v, w, tag;
	bool operator < (const node &b) const {
		return d > b.d;
	}
} a[N], b[N];
int n, len, last, maxw;
db t;
bool cmp(node a, node b) {
	return a.w > b.w;
}
db calc(node a) {
	return a.d + a.v * t;
}
fac calc(node a, node b) {
	if(a.d > b.d) swap(a, b);
	if(a.v > b.v) return fac(b.d - a.d, a.v - b.v);
	return fac(len - b.d + a.d, b.v - a.v);
}
void cdq(int l, int r) {
	if(l == r) return ;
	int mid = (l + r) >> 1;
	cdq(l, mid); cdq(mid + 1, r);

	db Max = -INF, Min = INF;
	int p = l;
	for(int i = mid + 1; i <= r; i ++) if(!a[i].tag) {
		for(; p <= mid && cmp(a[p], a[i]); p ++) {
			Max = max(Max, calc(a[p]));
			Min = min(Min, calc(a[p]));
		}
		if(Min <= calc(a[i]) || Max >= calc(a[i]) + len) {
			a[i].tag = 1;
		}
	}

	Max = -INF, Min = INF;
	p = mid + 1;
	for(int i = l; i <= mid; i ++) if(!a[i].tag) {
		for(; p <= r && cmp(a[p], a[i]); p ++) {
			Max = max(Max, calc(a[p]));
			Min = min(Min, calc(a[p]) + len);
		}
		if(Min <= calc(a[i]) || Max >= calc(a[i])) {
			a[i].tag = 1;
		}
	}

	static node tmp[N];
	int pl = l, pr = mid + 1;
	for(int i = l; i <= r; i ++) {
		if(pr > r || (pl <= mid && cmp(a[pl], a[pr]))) {
			tmp[i] = a[pl ++];
		} else {
			tmp[i] = a[pr ++];
		}
	}
	copy(tmp + l, tmp + r + 1, a + l);
}
bool check(db mid) {
	copy(b + 1, b + n + 1, a + 1);
	t = mid; cdq(1, n);
	for(int i = 1; i <= n; i ++)
		if(a[i].w < maxw && !a[i].tag) {
			last = a[i].d; return 0;
		}
	return 1;
}
int main() {
	// freopen("input", "r", stdin);
	int test;
	scanf("%d", &test);
	while(test --) {
		scanf("%d%d", &n, &len); maxw = 0;
		for(int i = 1; i <= n; i ++) scanf("%d", &b[i].d);
		for(int i = 1; i <= n; i ++) scanf("%d", &b[i].v);
		for(int i = 1; i <= n; i ++) {
			scanf("%d", &b[i].w);
			maxw = max(maxw, b[i].w);
			b[i].tag = 0;
		}
		sort(b + 1, b + n + 1);
		db l = 0, r = 1e9;
		while(r - l > 1e-5) {
			db mid = (l + r) / 2;
			if(check(mid)) r = mid;
			else l = mid;
		}
		if(l < 1e-10) puts("0");
		else {
			int id = 0;
			for(int i = 1; i <= n; i ++)
				if(b[i].d == last) {
					id = i; break ;
				}
			fac ans; bool fir = 1;
			for(int i = 1; i <= n; i ++) {
				if(b[i].w > b[id].w) {
					fac cur = calc(b[id], b[i]);
					if(fir) ans = cur, fir = 0;
					else ans = min(ans, cur);
				}
			}
			printf("%d/%d\n", ans.x, ans.y);
		}
	}
	return 0;
}
/*
d[j] > d[i] meet :
d[j] + v[j] * t <= d[i] + v[i] * t or
d[j] + v[j] * t >= d[i] + v[i] * t + l 
*/