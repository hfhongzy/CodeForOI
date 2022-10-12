#include <algorithm>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;
const int N = 510050;
int n, id = 1, cur, ch[N][26], sz[N];
vector<int> G[N];
bool tag[N];
void insert(char *s) {
	int u = 1;
	for(; *s; s ++) {
		int &v = ch[u][*s - 'a'];
		u = v ? v : v = ++ id; sz[u] ++;
	}
	tag[u] = 1;
}
long long ans;
bool cmp(int x, int y) {
	return sz[x] < sz[y];
}
void build(int u, int fa) {
	if(tag[u] || u == 1) {
		if(fa) G[fa].push_back(u);
		fa = u;
	}
	for(int i = 0; i < 26; i ++) if(ch[u][i]) {
		build(ch[u][i], fa);
	}
}
void dfs(int u, int dfn) {
	if(tag[u]) { cur ++; ans += cur - dfn; dfn = cur; }
	sort(G[u].begin(), G[u].end(), cmp);
	for(int i = 0; i < (int) G[u].size(); i ++) {
		dfs(G[u][i], dfn);
	}
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++) {
		static char s[N];
		scanf("%s", s);
		reverse(s, s + strlen(s));
		insert(s);
	}
	build(1, 0);
	dfs(1, 0);
	printf("%lld\n", ans);
	return 0;
}