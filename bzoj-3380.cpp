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
void ins(int &u, int l, int r, int pre = 0) {
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

int main() {
	freopen("input", "r", stdin);
	return 0;
}