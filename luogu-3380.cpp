#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
const int N = 1e5 + 10;
const int T = 24 * N;
const int INF = 2147483647;
int n, m, low, up, cur, a[N], pos[N], rt[N << 2], id, fa[T], ch[T][2], sz[T], cnt[T], w[T];
inline void upd(int u) {
	sz[u] = cnt[u] + sz[ch[u][0]] + sz[ch[u][1]];
}
inline int dir(int u) { return ch[fa[u]][1] == u; }
void ins(int &u, int w0, int pre = 0) {
	if(!u) {
		u = ++ id; fa[u] = pre; w[u] = w0;
		cnt[u] = sz[u] = 1; cur = u; return ;
	}
	if(w0 == w[u]) { cnt[u] ++; sz[u] ++; cur = u; }
	else { ins(ch[u][w0 > w[u]], w0, u); upd(u); }
}
void rotate(int u) {
	int d = dir(u), f = fa[u];
	if(fa[u] = fa[f]) ch[fa[u]][dir(f)] = u;
	if(ch[f][d] = ch[u][d ^ 1]) fa[ch[f][d]] = f;
	fa[ch[u][d ^ 1] = f] = u; upd(f); upd(u);
}
void splay(int bl, int u) {
	for(; fa[u]; rotate(u)) {
		int y = fa[u], z = fa[y];
		if(z) {
			rotate(((ch[y][1] == u) ^ (ch[z][1] == y)) ? y : u);
		}
	}
	rt[bl] = u;
}
int find(int bl, int w0) {
	int u = rt[bl];
	while(ch[u][w0 > w[u]] && w0 != w[u]) {
		u = ch[u][w0 > w[u]];
	}
	splay(bl, u);
	return u;
}
int pre(int bl, int w0) {
	int u = find(bl, w0);
	if(w[u] < w0) return u;
	for(u = ch[u][0]; ch[u][1]; u = ch[u][1]) ;
	return u;
}
int nxt(int bl, int w0) {
	int u = find(bl, w0);
	if(w[u] > w0) return u;
	for(u = ch[u][1]; ch[u][0]; u = ch[u][0]) ;
	return u;
}
void del(int bl, int w0) {
	int u = find(bl, w0);
	if(cnt[u] > 1) { cnt[u] --; sz[u] --; return ; }
	if(!ch[u][0]) { fa[ch[u][1]] = 0; rt[bl] = ch[u][1]; return ; }
	if(!ch[u][1]) { fa[ch[u][0]] = 0; rt[bl] = ch[u][0]; return ; }
	int l = ch[u][0], r = ch[u][1]; fa[l] = 0;
	while(ch[l][1]) l = ch[l][1];
	splay(bl, l); ch[l][1] = r; fa[r] = l; upd(l);
}
int rnk(int bl, int w) { //count '<'
	int u = find(bl, w);
	return sz[ch[u][0]] + (::w[u] >= w ? 0 : cnt[u]);
}
namespace seg {

int tmp[N];
void build(int u, int l, int r) {
	copy(a + l, a + r + 1, tmp + l);
	random_shuffle(tmp + l, tmp + r + 1);
	for(int i = l; i <= r; i ++) {
		ins(rt[u], tmp[i]);
	}
	splay(u, cur);
	if(l == r) { pos[l] = u; return ; }
	int mid = (l + r) >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
}
int qrnk(int u, int l, int r, int ql, int qr, int w) {
	if(l == ql && r == qr) return rnk(u, w);
	int mid = (l + r) >> 1;
	if(qr <= mid) return qrnk(u << 1, l, mid, ql, qr, w);
	if(ql > mid) return qrnk(u << 1 | 1, mid + 1, r, ql, qr, w);
	return qrnk(u << 1, l, mid, ql, mid, w) +
	qrnk(u << 1 | 1, mid + 1, r, mid + 1, qr, w);
}
int qkth(int ql, int qr, int k) {
	int l = low, r = up;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(qrnk(1, 1, n, ql, qr, mid) < k) l = mid + 1;
		else r = mid - 1;
	}
	return l - 1;
}
void modify(int p, int v) {
	low = min(low, v); up = max(up, v);
	for(int u = pos[p]; u; u >>= 1) {
		del(u, a[p]); ins(rt[u], v); splay(u, cur);
	}
	a[p] = v;
}
int qpre(int u, int l, int r, int ql, int qr, int w) {
	if(l == ql && r == qr) {
		int x = pre(u, w);
		return !x ? -INF : (::w[x]);
	}
	int mid = (l + r) >> 1;
	if(qr <= mid) return qpre(u << 1, l, mid, ql, qr, w);
	if(ql > mid) return qpre(u << 1 | 1, mid + 1, r, ql, qr, w);
	return max(qpre(u << 1, l, mid, ql, mid, w), 
		qpre(u << 1 | 1, mid + 1, r, mid + 1, qr, w));
}
int qnxt(int u, int l, int r, int ql, int qr, int w) {
	if(l == ql && r == qr) {
		int x = nxt(u, w);
		return !x ? INF : (::w[x]);
	}
	int mid = (l + r) >> 1;
	if(qr <= mid) return qnxt(u << 1, l, mid, ql, qr, w);
	if(ql > mid) return qnxt(u << 1 | 1, mid + 1, r, ql, qr, w);
	return min(qnxt(u << 1, l, mid, ql, mid, w),
		qnxt(u << 1 | 1, mid + 1, r, mid + 1, qr, w));
}

}

int main() {
	freopen("input", "r", stdin);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++) scanf("%d", a + i);
	low = *min_element(a + 1, a + n + 1);
	up = *max_element(a + 1, a + n + 1);
	seg::build(1, 1, n);
	for(int i = 1, op, l, r, k; i <= m; i ++) {
		scanf("%d%d%d", &op, &l, &r);
		if(op ^ 3) scanf("%d", &k);
		if(op == 1) printf("%d\n", seg::qrnk(1, 1, n, l, r, k) + 1);
		if(op == 2) printf("%d\n", seg::qkth(l, r, k));
		if(op == 3) seg::modify(l, r);
		if(op == 4) printf("%d\n", seg::qpre(1, 1, n, l, r, k));
		if(op == 5) printf("%d\n", seg::qnxt(1, 1, n, l, r, k));
	}
	return 0;
}