#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
const int N = 2e5 + 10;
char str[N];
int id, n, maxc, la, nxt[N][26], len[N], lnk[N], a[N], w[N];
void clr(int x) { fill(nxt[x], nxt[x] + maxc, -1); }
vector<int> G[N];
void init() {
	fill(w + 1, w + id + 1, 0);
	for(int i = 0; i <= id; i ++) G[i].clear();
	id = la = len[0] = 0; lnk[0] = -1; clr(0);
}
void extend(int c) {
	int u = ++ id, p = la;
	len[u] = len[la] + 1; clr(u);
	for(; ~ p && -1 == nxt[p][c]; p = lnk[p]) {
		nxt[p][c] = u; G[p].push_back(c);
	}
	if(p == -1) lnk[u] = 0;
	else {
		int q = nxt[p][c];
		if(len[p] + 1 == len[q]) {
			lnk[u] = q;
		} else {
			int q0 = ++ id; G[q0] = G[q];
			copy(nxt[q], nxt[q] + maxc, nxt[q0]);
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
	static int cnt[N];
	int n = len[la]; fill(cnt, cnt + n + 1, 0);
	for(int i = 1; i <= id; i ++) cnt[len[i]] ++;
	for(int i = 1; i <= n; i ++) cnt[i] += cnt[i - 1];
	for(int i = 1; i <= id; i ++) a[cnt[len[i]] --] = i;
	for(int i = id; i >= 1; i --) {
		int u = a[i], f = lnk[u]; w[f] += w[u];
	}
}
long long dfs(int u, int l, int c) {
	if(c == 4) return 0ll;
	if(!str[l + 1]) return w[u];
	long long ans = 0;
	for(int v = 0; v < (int) G[u].size(); v ++) {
		int i = G[u][v];
		ans += dfs(nxt[u][i], l + 1, c + ( i != str[l + 1] - 'A' ));
	}
	return ans;
}
int main() {
	freopen("input", "r", stdin);
	int test; scanf("%d", &test);
	while(test --) {
		scanf("%s", str); maxc = 1;
		for(int i = 0; str[i]; i ++) maxc = max(maxc, str[i] - 'A' + 1);
		init();
		for(int i = 0; str[i]; i ++) extend(str[i] - 'A');
		scanf("%s", str); tpo();
		printf("%lld\n", dfs(0, -1, 0));
	}
	return 0;
}