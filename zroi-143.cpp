#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 5e6 + 5, M = N * 2;
int n, pos[N], nxt[M][5], id, la, len[M], lnk[M];
bool tag[M];
void clr(int u) { fill(nxt[u], nxt[u] + 5, -1); }
void init() { la = id = 0; len[0] = 0; clr(0); lnk[0] = -1; }
void extend(int c) {
	int u = ++ id, p = la; clr(u); len[u] = len[la] + 1;
	for(; ~ p && -1 == nxt[p][c]; p = lnk[p]) nxt[p][c] = u;
	if(p == -1) lnk[u] = 0;
	else {
		int q = nxt[p][c];
		if(len[p] + 1 == len[q]) lnk[u] = q;
		else {
			int q0 = ++ id;
			copy(nxt[q], nxt[q] + 5, nxt[q0]);
			len[q0] = len[p] + 1; lnk[q0] = lnk[q];
			lnk[q] = lnk[u] = q0;
			for(; ~ p && nxt[p][c] == q; p = lnk[p]) nxt[p][c] = q0;
		}
	}
	la = u; pos[len[u]] = u;
}
int q[N], g[N], val[N], l, r;
int main() {
	static char s[N]; scanf("%s", s); init();
	for(int i = 0; s[i]; i ++) extend(s[i] - 'a');
	fill(tag + 1, tag + id + 1, 1);
	for(int i = 1; i <= id; i ++) tag[lnk[i]] = 0;
	n = len[la]; fill(val + 1, val + n + 1, n + 1);
	for(int i = 1; i <= n; i ++) {
		int u = pos[i], mid = i - len[lnk[u]];
		if(tag[u]) {
			g[i] = len[lnk[u]] + 1;
			val[mid]	= min(val[mid], i);
		}
	}
	for(int i = n; i >= 1; i --)
		val[i - 1] = min(val[i - 1], val[i]);
	for(int i = 1; i <= n; i ++) {
		if(val[i] > n) val[i] = n;
		else val[i] = val[i] - i + 1;
	}
	for(int i = n; i >= 1; i --) {
		int u = pos[i];
		while(l < r && q[l] - g[q[l]] + 1 >= i) l ++;
		if(g[i]) {
			while(l < r && g[q[r - 1]] >= g[i]) r --;
			q[r ++] = i;
		}
		if(l ^ r) val[i] = min(val[i], g[q[l]]);
	}
	long long ans = 0;
	for(int i = 1; i <= n; i ++) ans += val[i];
	printf("%lld\n", ans);
	return 0;
}