#include <algorithm>
#include <cstring>
#include <cassert>
#include <cstdio>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
const int mod1 = 19260817, mod2 = 1e9 + 9, base = 1333;
ll pw1[N], pw2[N];
char str[N];
void init() {
	pw1[0] = pw2[0] = 1;
	for(int i = 1; i < N; i ++) {
		pw1[i] = pw1[i - 1] * base % mod1;
		pw2[i] = pw2[i - 1] * base % mod2;
	}
}
int n, m, rt, id, fa[N], ch[N][2], h1[N], h2[N], sz[N], w[N];
void upd(int u) {
	int &ls = ch[u][0], &rs = ch[u][1];
	sz[u] = 1 + sz[ls] + sz[rs];
	h1[u] = (h1[ls] * pw1[sz[rs] + 1] + w[u] * pw1[sz[rs]] + h1[rs]) % mod1;
	h2[u] = (h2[ls] * pw2[sz[rs] + 1] + w[u] * pw2[sz[rs]] + h2[rs]) % mod2;
}
int dir(int u) { return ch[fa[u]][1] == u; }
void build(int &u, int l, int r, int pre = 0) {
	if(l > r) return ;
	int mid = (l + r) >> 1;
	u = ++ id; fa[u] = pre; w[u] = str[mid];
	build(ch[u][0], l, mid - 1, u);
	build(ch[u][1], mid + 1, r, u);
	upd(u);
}
void rotate(int u) {
	int d = dir(u), f = fa[u];
	if(fa[u] = fa[f]) ch[fa[u]][dir(f)] = u;
	if(ch[f][d] = ch[u][d ^ 1]) fa[ch[f][d]] = f;
	fa[ch[u][d ^ 1] = f] = u; upd(f); upd(u);
}
void splay(int u, int top = 0) {
	for(; fa[u] != top; rotate(u)) if(fa[fa[u]] != top)
		rotate(dir(u) == dir(fa[u]) ? fa[u] : u);
	if(!top) rt = u;
}
int kth(int u, int k) {
	int v = u;
	while(1) {
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
void prehash(int &v1, int &v2, int p) { //p \in [1, n + 2]
	int v = kth(rt, p + 1); v = ch[v][0];
	v1 = h1[v]; v2 = h2[v];
}
void qryhash(int &v1, int &v2, int l, int r) { // l, r \in [1, n + 2]
	int l1, l2, r1, r2; prehash(r1, r2, r); prehash(l1, l2, l - 1);
	v1 = (r1 - l1 * pw1[r - l + 1] % mod1 + mod1) % mod1;
	v2 = (r2 - l2 * pw2[r - l + 1] % mod2 + mod2) % mod2;
}
bool equal(int u, int v, int l) { // u, v \in [1, n]
	if(u == v) return 1;
	int u1, u2, v1, v2;
	qryhash(u1, u2, u + 1, u + l);
	qryhash(v1, v2, v + 1, v + l);
	return u1 == v1 && u2 == v2;
}
int query(int x, int y) {
	if(!equal(x, y, 1)) return 0;
	int l = 1, r = min(n - x + 1, n - y + 1);
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(equal(x, y, mid)) l = mid + 1;
		else r = mid - 1;
	}
	return l - 1;
}
void modify(int k, int w0) {
	int v = kth(rt, k + 1); w[v] = w0; upd(v);
}
void insert(int p, int w0) {
	int v = kth(rt, p + 1); id ++; w[id] = w0;
	ch[id][1] = ch[v][1]; fa[ch[v][1]] = id; ch[v][1] = 0;
	ch[id][0] = v; fa[v] = id; upd(v); upd(id); rt = id;
}
int main() {
	freopen("input", "r", stdin);
	init();
	scanf("%s%d", str + 1, &m);
	build(rt, 0, 1 + (n = strlen(str + 1)));
	char op[4], op2[4]; int x, y;
	for(int i = 1; i <= m; i ++) {
		scanf("%s%d", op, &x);
		if(*op == 'Q') { scanf("%d", &y); printf("%d\n", query(x, y)); }
		if(*op == 'R') { scanf("%s", op2); modify(x, *op2); }
		if(*op == 'I') { scanf("%s", op2); n ++; insert(x, *op2); }
	}
	return 0;
}