#include <algorithm>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
char str[N];
int id, la, nxt[N][26], len[N], slen[3], lnk[N], a[N], w[N];
void clr(int x) { fill(nxt[x], nxt[x] + 26, -1); }
void init() { id = la = len[0] = 0; lnk[0] = -1; clr(0); }
void extend(int c) {
	int u = ++ id, p = la;
	len[u] = len[la] + 1; clr(u);
	for(; ~ p && -1 == nxt[p][c]; p = lnk[p]) {
		nxt[p][c] = u;
	}
	if(p == -1) lnk[u] = 0;
	else {
		int q = nxt[p][c];
		if(len[p] + 1 == len[q]) {
			lnk[u] = q;
		} else {
			int q0 = ++ id;
			copy(nxt[q], nxt[q] + 26, nxt[q0]);
			len[q0] = len[p] + 1; lnk[q0] = lnk[q];
			lnk[q] = lnk[u] = q0;
			for(; ~ p && nxt[p][c] == q; p = lnk[p]) {
				nxt[p][c] = q0;
			}
		}
	}
	la = u; w[u] = 1;
}
void tpo() {
	static int cnt[N]; int n = len[la];
	for(int i = 1; i <= id; i ++) cnt[len[i]] ++;
	for(int i = 1; i <= n; i ++) cnt[i] += cnt[i - 1];
	for(int i = 1; i <= id; i ++) a[cnt[len[i]] --] = i;
	for(int i = id; i >= 1; i --) {
		int u = a[i], f = lnk[u]; w[f] += w[u];
	}
}
int t, k;
ll ans[N];
bool vis[N];
ll dfs(int u) {
	if(vis[u]) return ans[u];
	vis[u] = 1; ans[u] = t ? w[u] : (u >= 1);
	for(int i = 0; i < 26; i ++) {
		int v = nxt[u][i];
		if(~ v) ans[u] += dfs(v);
	}
	return ans[u];
}
int main() {
	freopen("input", "r", stdin);
	scanf("%s%d%d", str, &t, &k);
	init();
	for(int i = 0; str[i]; i ++) extend(str[i] - 'a');
	if(t) tpo(); dfs(0);
	if(k > ans[0]) return puts("-1"), 0;
	ans[0] = w[0] = 0;
	int u = 0; string s;
	while(1) {
		if(k <= (t ? w[u] : (u >= 1))) {
			break ;
		}
		k -= (t ? w[u] : (u >= 1));
		for(int i = 0; i < 26; i ++) {
			int v = nxt[u][i];
			if(v == -1) continue ;
			if(k <= ans[v]) {
				putchar(i + 'a');
				u = v; break ;
			} else {
				k -= ans[v];
			}
		}
	}
	putchar('\n');
	return 0;
}
/*
ans[u]表示u为起点有多少个串
*/