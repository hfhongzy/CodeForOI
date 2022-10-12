#include <algorithm>
#include <cstdio>
#include <queue>
#define fs first
#define sc second
using namespace std;
double sqr(double x) { return x * x; }
void cmin(int &x, const int &y) { x = min(x, y); }
void cmax(int &x, const int &y) { x = max(x, y); }
const int N = 2e5 + 10;
int n, k, q;
struct point {
	int x[5];
	void input() {
		for(int i = 0; i < k; i ++) {
			scanf("%d", x + i);
		}
	}
	void output() const {
		for(int i = 0; i < k; i ++) {
			printf("%d%c", x[i], " \n"[i == k - 1]);
		}
	}
	double dto(const point &b) const {
		double d = 0;
		for(int i = 0; i < k; i ++) {
			d += sqr(x[i] - b.x[i]);
		}
		return d;
	}
} a[N];
int ls[N], rs[N], cmp_p, lim[2][N][5];
bool cmp(const point &a, const point &b) {
	return a.x[cmp_p] < b.x[cmp_p];
}
void upd(int u) {
	for(int i = 0; i < k; i ++) {
		lim[0][u][i] = lim[1][u][i] = a[u].x[i];
	}
	if(ls[u]) {
		for(int i = 0; i < k; i ++) {
			cmin(lim[0][u][i], lim[0][ls[u]][i]);
			cmax(lim[1][u][i], lim[1][ls[u]][i]);
		}
	}
	if(rs[u]) {
		for(int i = 0; i < k; i ++) {
			cmin(lim[0][u][i], lim[0][rs[u]][i]);
			cmax(lim[1][u][i], lim[1][rs[u]][i]);
		}
	}
}
double mindis(int u, const point &b) {
	if(u == 0) return 2e9;
	double ans = 0;
	for(int i = 0; i < k; i ++) {
		if(b.x[i] < lim[0][u][i]) ans += sqr(b.x[i] - lim[0][u][i]);
		if(b.x[i] > lim[1][u][i]) ans += sqr(b.x[i] - lim[1][u][i]);
	}
	return ans;
}
int build(int l, int r) {
	if(l > r) return 0;
	double z[5] = {0}; cmp_p = 0;
	int u = (l + r) >> 1;
	for(int j = 0; j < k; j ++) {
		double x = 0;
		for(int i = l; i <= r; i ++) {
			x += a[i].x[j];
		}
		x /= r - l + 1;
		for(int i = l; i <= r; i ++) {
			z[j] += sqr(a[i].x[j] - x);
		}
		if(z[cmp_p] < z[j]) cmp_p = j;
	}
	nth_element(a + l, a + u, a + r + 1, cmp);
	ls[u] = build(l, u - 1); rs[u] = build(u + 1, r);
	upd(u); return u;
}
typedef pair< point, double > node;
struct pqcmp {
	bool operator () (const node &a, const node &b) const {
		return a.sc < b.sc;
	}
};
point qa; int qm;
priority_queue< node, vector<node>, pqcmp > pq;
bool uper(double x) {
	return pq.size() < qm || pq.top().sc > x;
}
void query(int l, int r) {
	if(l > r) return ;
	int u = (l + r) >> 1;
	double d = a[u].dto(qa);
	if(pq.size() < qm) pq.push(make_pair(a[u], d));
	else if(d < pq.top().sc) {
		pq.pop(); pq.push(make_pair(a[u], d));
	}
	double ld = mindis(ls[u], qa), rd = mindis(rs[u], qa);
	if(uper(ld) && uper(rd)) {
		if(ld < rd) {
			query(l, u - 1);
			if(uper(rd)) query(u + 1, r);
		} else {
			query(u + 1, r);
			if(uper(ld)) query(l, u - 1);
		}
	} else if(uper(ld)) query(l, u - 1);
	else if(uper(rd)) query(u + 1, r);
}
int main() {
	while(~ scanf("%d%d", &n, &k)) {
		for(int i = 1; i <= n; i ++) {
			a[i].input();
		}
		build(1, n);
		scanf("%d", &q);
		vector<point> ans;
		for(int i = 1; i <= q; i ++) {
			qa.input(); scanf("%d", &qm);
			printf("the closest %d points are:\n", qm);
			query(1, n); ans.clear();
			while(pq.size()) {
				ans.push_back(pq.top().fs);
				pq.pop();
			}
			for(int j = (int) ans.size() - 1; j >= 0; j --) {
				ans[j].output();
			}
			while(pq.size()) pq.pop();
		}
	}
	return 0;
}