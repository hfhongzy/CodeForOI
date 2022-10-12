#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
struct Edge { int v, w; };
int n, m, q, a[N], b[N];
ll tag[N << 2], Min[N << 2], seq[N], res[N];
vector<Edge> G[N];
void build(int u, int l, int r) {
	tag[u] = 0;
	if(l == r) { Min[u] = seq[l]; return ; }
	int mid = (l + r) >> 1;
	build(u << 1, l, mid); build(u << 1 | 1, mid + 1, r);
	Min[u] = min(Min[u << 1], Min[u << 1 | 1]);
}
void addtag(int u, ll v) {
	Min[u] += v; tag[u] += v;
}
void down(int u) {
	if(tag[u]) {
		addtag(u << 1, tag[u]);
		addtag(u << 1 | 1, tag[u]);
		tag[u] = 0;
	}
}
void modify(int u, int l, int r, int ql, int qr, int v) {
	if(l == ql && r == qr) { addtag(u, v); return ; }
	int mid = (l + r) >> 1; down(u);
	if(qr <= mid) modify(u << 1, l, mid, ql, qr, v);
	else if(ql > mid) modify(u << 1 | 1, mid + 1, r, ql, qr, v);
	else {
		modify(u << 1, l, mid, ql, mid, v);
		modify(u << 1 | 1, mid + 1, r, mid + 1, qr, v);
	}
	Min[u] = min(Min[u << 1], Min[u << 1 | 1]);
}
int main() {
	freopen("input", "r", stdin);
	scanf("%d%d%d", &n, &m, &q);
	for(int i = 1; i < n; i ++) scanf("%d%d", a + i, b + i);
	for(int u, v, w, i = 1; i <= m; i ++) {
		scanf("%d%d%d", &u, &v, &w);
		G[u].push_back({v, w});
	}
	copy(b + 1, b + n + 1, seq + 2); build(1, 1, n);
	for(int x = 1; x <= n; x ++) {
		for(auto &e : G[x]) {
			modify(1, 1, n, 1, e.v, e.w);
		}
		res[x] = Min[1];
	}
	for(int i = 1; i <= n; i ++) seq[i] = res[i] + a[i];
	build(1, 1, n); printf("%lld\n", Min[1]);
	for(int u, w, i = 1; i <= q; i ++) {
		scanf("%d%d", &u, &w);
		modify(1, 1, n, u, u, w - a[u]); a[u] = w;
		printf("%lld\n", Min[1]);
	}
	return 0;
}
//a[x] : x to x + 1; b[y] : y - 1 to y
//a[x] + b[y] + \sum_{(x) >= u, (y) <= v} w; seg maintain y
//a[x] + res[x]