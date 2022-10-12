#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 150050;
int n, m, a[N], p[N], x[N], l, r, cnt[N * 4];
struct node {
	int mv, mpos;
	node operator + (const node &b) {
		node ans = (node) {min(b.mv, mv), 0};
		if(mv == ans.mv) ans.mpos += mpos;
		if(b.mv == ans.mv) ans.mpos += b.mpos;
		return ans;
	}
} _min[N * 15];
int tag[N * 15];
void addtag(int u, int d) { tag[u] += d; _min[u].mv += d; }
void pushd(int u) {
	if(tag[u]) {
		addtag(u << 1, tag[u]);
		addtag(u << 1 | 1, tag[u]);
		tag[u] = 0;
	}
}
void build(int u, int l, int r) {
	_min[u].mpos = r - l + 1; _min[u].mv = 0;
	if(l == r) return ;
	int mid = l + (r - l) / 2;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
}
void modify(int u, int l, int r, int ql, int qr, int k) {
	if(l == ql && r == qr) { addtag(u, k); return ; }
	int mid = l + (r - l) / 2; pushd(u);
	if(qr <= mid) modify(u << 1, l, mid, ql, qr, k);
	else if(ql > mid) modify(u << 1 | 1, mid + 1, r, ql, qr, k);
	else {
		modify(u << 1, l, mid, ql, mid, k);
		modify(u << 1 | 1, mid + 1, r, mid + 1, qr, k);
	}
	_min[u] = _min[u << 1] + _min[u << 1 | 1];
}
node query(int u, int l, int r, int ql, int qr) {
	if(l == ql && r == qr) return _min[u];
	int mid = l + (r - l) / 2; pushd(u);
	if(qr <= mid) return query(u << 1, l, mid, ql, qr);
	if(ql > mid) return query(u << 1 | 1, mid + 1, r, ql, qr);
	return query(u << 1, l, mid, ql, mid) + query(u << 1 | 1, mid + 1, r, mid + 1, qr);
}
bool range(int x) { return l <= x && x <= r; }
void dec(int x) {
	int pos = x - cnt[x + 2 * N] + 1;
	if(range(x))
		modify(1, -N, 2 * N, pos, pos, -1);
	cnt[x + 2 * N] --;
}
void add(int x) {
	cnt[x + 2 * N] ++;
	int pos = x - cnt[x + 2 * N] + 1;
	if(range(x))
		modify(1, -N, 2 * N, pos, pos, 1);
}
void push(int x) {
	if(cnt[x + 2 * N]) {
		modify(1, -N, 2 * N, x - cnt[x + 2 * N] + 1, x, 1);
	}
}
void pop(int x) {
	if(cnt[x + 2 * N]) {
		modify(1, -N, 2 * N, x - cnt[x + 2 * N] + 1, x, -1);
	}
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++) scanf("%d", a + i);
	for(int i = 1; i <= m; i ++) scanf("%d%d", p + i, x + i);
	for(int i = 1; i <= n; i ++) cnt[a[i] + 2 * N] ++;
	build(1, - N, 2 * N);
	for(int i = 1; i <= n; i ++) if(cnt[i + 2 * N])
		modify(1, - N, 2 * N, i - cnt[i + 2 * N] + 1, i, 1);
	l = 1; r = n; int sumx = 0;
	for(int i = 1; i <= m; i ++) {
		if(p[i] == 0) {
			sumx += x[i];
			if(x[i] == 1) { push(-- l); pop(r --); }
			else { push(++ r); pop(l ++); }
		} else { dec(a[p[i]]); add(a[p[i]] = x[i] - sumx); }
		node tmp = query(1, -N, 2 * N, l, r);
		printf("%d\n", tmp.mv == 0 ? tmp.mpos : 0);
	}
	return 0;
}