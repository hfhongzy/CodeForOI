#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
const int N = 65534 + 10, M = 4e5 + 10;
int n, d[N], sz[N], rdg[N], seq[N], s, f[N][17];
vector<int> G[N], fG[N];
void link(int u, int fa) {
	f[u][0] = fa; d[u] = d[fa] + 1;
	for(int i = 1; i < 17; i ++)
		f[u][i] = f[f[u][i - 1]][i - 1];
}
int lca(int u, int v) {
	if(!u || !v) return u | v;
	if(d[u] < d[v]) swap(u, v);
	int c = d[u] - d[v];
	for(int i = 16; ~ i; i --)
		if(c >> i & 1) u = f[u][i];
	if(u == v) return u;
	for(int i = 16; ~ i; i --)
		if(f[u][i] ^ f[v][i]) {
			u = f[u][i]; v = f[v][i];
		}
	return f[u][0];
}
int main() {
	scanf("%d", &n);
	for(int x, i = 1; i <= n; i ++) {
		while(scanf("%d", &x), x) {
			fG[i].push_back(x);
			G[x].push_back(i); rdg[i] ++;
		}
	}
	for(int i = 1; i <= n; i ++)
		if(!rdg[i]) {
			G[n + 1].push_back(i);
			fG[i].push_back(n + 1); rdg[i] = 1;
		}
	static int q[N], ql, qr; q[qr ++] = n + 1;
	while(ql < qr) {
		int u = q[ql ++]; seq[++ s] = u;
		int fa = 0;
		for(int i = 0; i < (int) fG[u].size(); i ++)
			fa = lca(fa, fG[u][i]);
		if(fa) link(u, fa);
		for(int i = 0; i < (int) G[u].size(); i ++) {
			int v = G[u][i];
			if(!-- rdg[v]) q[qr ++] = v;
		}
	}
	for(int i = n + 1; i >= 1; i --) {
		int u = seq[i]; sz[u] ++; sz[f[u][0]] += sz[u];
	}
	for(int i = 1; i <= n; i ++)
		printf("%d\n", sz[i] - 1);
	return 0;
}