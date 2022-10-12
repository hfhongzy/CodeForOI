#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
typedef unsigned long long ull;
const int N = 2e5 + 10;
const int base = 1333;
ull pw1[N];
char str[N];
void init() {
	pw1[0] = 1;
	for(int i = 1; i < N; i ++) {
		pw1[i] = pw1[i - 1] * base;
	}
}
int n, m, rt, id, fa[N], ch[N][2], sz[N], w[N];
ull h1[N];
void upd(int u) {
	int &ls = ch[u][0], &rs = ch[u][1];
	sz[u] = 1 + sz[ls] + sz[rs];
	h1[u] = h1[ls] * pw1[sz[rs] + 1] + w[u] * pw1[sz[rs]] + h1[rs];
}
void upd2(int u) {
	int &ls = ch[u][0], &rs = ch[u][1];
	h1[u] = h1[ls] * pw1[sz[rs] + 1] + w[u] * pw1[sz[rs]] + h1[rs];
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
ull prehash(int p) { //p \in [1, n + 2]
	return h1[ch[kth(rt, p + 1)][0]];
}
ull qryhash(int l, int r) { // l, r \in [1, n + 2]
	return prehash(r) - prehash(l - 1) * pw1[r - l + 1];
}
bool equal(int u, int v, int l) { // u, v \in [1, n]
	return qryhash(u + 1, u + l) == qryhash(v + 1, v + l);
}
int query(int x, int y) {
	if(x == y) return n - x + 1;
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
	int v = kth(rt, k + 1); w[v] = w0; upd2(v);
}
void insert(int p, int w0) {
	int v = kth(rt, p + 1); id ++; w[id] = w0;
	ch[id][1] = ch[v][1]; fa[ch[v][1]] = id; ch[v][1] = 0;
	ch[id][0] = v; fa[v] = id; upd(v); upd(id); rt = id;
}
int main() {
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