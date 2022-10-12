#include <algorithm>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;
const int N = 1e6 + 10;
const int null = - 1926;
int n, m, rt, id, fa[N], ch[N][2], sz[N], w[N];
int tag[N], lsum[N] = {null}, rsum[N] = {null}, ans[N] = {null}, sum[N], seq[N], a[N];
bool rev[N];
int dir(int u) { return ch[fa[u]][1] == u; }
queue<int> q;
void delnode(int u) {
	q.push(u);
	if(fa[u]) ch[fa[u]][dir(u)] = 0;
	if(ch[u][0]) fa[ch[u][0]] = 0;
	if(ch[u][1]) fa[ch[u][1]] = 0;
}
int newnode(int w0) {
	int u = 0;
	if(q.size()) { u = q.front(); q.pop(); }
	else u = ++ id;
	fa[u] = ch[u][0] = ch[u][1] = rev[u] = 0;
	w[u] = w0; tag[u] = null;
	return u;
}
void upd(int u) {
	int &ls = ch[u][0], &rs = ch[u][1];
	sz[u] = 1 + sz[ls] + sz[rs];
	sum[u] = w[u] + sum[ls] + sum[rs];
	lsum[u] = max(lsum[ls], sum[ls] + w[u] + max(0, lsum[rs]));
	rsum[u] = max(rsum[rs], sum[rs] + w[u] + max(0, rsum[ls]));
	ans[u] = max(max(ans[ls], ans[rs]), max(rsum[ls], 0) + w[u] + max(lsum[rs], 0));
}
void mktag(int u, int w0) {
	if(u == 0) return ;
	w[u] = tag[u] = w0; sum[u] = sz[u] * w0;
	ans[u] = lsum[u] = rsum[u] = w0 >= 0 ? sum[u] : w0;
}
void revtag(int u) {
	if(u == 0) return ;
	rev[u] ^= 1; swap(lsum[u], rsum[u]);
}
void down(int u) {
	int &ls = ch[u][0], &rs = ch[u][1];
	if(rev[u]) { revtag(ls); revtag(rs); swap(ls, rs); rev[u] = 0; }
	if(tag[u] ^ null) { mktag(ls, tag[u]); mktag(rs, tag[u]); tag[u] = null; }
}
void build(int &u, int l, int r, int pre = 0) {
	if(l > r) return ;
	int mid = (l + r) >> 1;
	a[mid] = u = newnode(seq[mid]); fa[u] = pre;
	build(ch[u][0], l, mid - 1, u);
	build(ch[u][1], mid + 1, r, u);
	upd(u);
}
void recycle(int u) {
	if(u) {
		down(u);
		recycle(ch[u][0]);
		recycle(ch[u][1]);
		delnode(u);
	}
}
void rotate(int u) {
	int d = dir(u), f = fa[u];
	if(fa[u] = fa[f]) ch[fa[u]][dir(f)] = u;
	if(ch[f][d] = ch[u][d ^ 1]) fa[ch[f][d]] = f;
	fa[ch[u][d ^ 1] = f] = u; upd(f); upd(u);
}
int st[N];
void splay(int u, int top = 0) {
	int t = 0;
	for(int v = u; v; v = fa[v]) st[++ t] = v;
	while(t) down(st[t --]);
	for(; fa[u] != top; rotate(u)) if(fa[fa[u]] != top)
		rotate(dir(u) == dir(fa[u]) ? fa[u] : u);
	if(!top) rt = u;
}
int kth(int u, int k) {
	int v = u;
	while(1) {
		down(v);
		if(k <= sz[ch[v][0]]) v = ch[v][0];
		else {
			k -= sz[ch[v][0]] + 1;
			if(k <= 0) break ;
			v = ch[v][1];
		}
	}
	splay(v, fa[u]);
	return v;
}
void del(int pos, int len) {
	int v = kth(rt, pos + len);
	int u = kth(ch[v][0], pos - 1);
	recycle(ch[u][1]); upd(u); upd(v);
}
int query_sum(int pos, int len) {
	int v = kth(rt, pos + len);
	int u = kth(ch[v][0], pos - 1);
	return sum[ch[u][1]];
}
void reverse(int pos, int len) {
	int v = kth(rt, pos + len);
	int u = kth(ch[v][0], pos - 1);
	revtag(ch[u][1]); upd(u); upd(v);
}
void make_same(int pos, int len, int val) {
	int v = kth(rt, pos + len);
	int u = kth(ch[v][0], pos - 1);
	mktag(ch[u][1], val); upd(u); upd(v);
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++) scanf("%d", seq + i);
	seq[0] = seq[n + 1] = null;
	build(rt, 0, n + 1); char op[20];
	for(int q = 1, x, y, z; q <= m; q ++) {
		scanf("%s", op);
		if(*op == 'I') {
			scanf("%d%d", &x, &n);
			for(int i = 1; i <= n; i ++) scanf("%d", seq + i);
			build(y, 1, n);
			int v = kth(rt, x + 1);
			int u = ch[v][1]; ch[v][1] = fa[u] = 0; upd(v);
			//v -> y -> u
			fa[u] = a[n]; ch[a[n]][1] = u; 
			fa[v] = a[1]; ch[a[1]][0] = v;
			splay(v); splay(u);
		}
		if(*op == 'D') { scanf("%d%d", &x, &y); del(x + 1, y); }
		if(*op == 'G') { scanf("%d%d", &x, &y); printf("%d\n", query_sum(x + 1, y)); }
		if(*op == 'R') { scanf("%d%d", &x, &y); reverse(x + 1, y); }
		if(*op == 'M') {
			if(op[2] == 'K') { scanf("%d%d%d", &x, &y, &z); make_same(x + 1, y, z); }
			else printf("%d\n", ans[rt]);
		}
	}
	return 0;
}