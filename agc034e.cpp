#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
const int N = 2020;
int n, rt, cnt[N], sum[N], son[N], f[N];
vector<int> G[N];
char s[N];
void dfs(int u, int d = 0, int fa = 0) {
	son[u] = 0; cnt[u] = s[u] == '1'; sum[u] = 0; f[u] = 0;
	for(int i = 0; i < (int) G[u].size(); i ++) {
		int v = G[u][i];
		if(v != fa) {
			dfs(v, d + 1, u);
			sum[u] += (sum[v] += cnt[v]);
			cnt[u] += cnt[v];
			if(sum[v] > sum[son[u]]) son[u] = v;
		}
	}
	if(sum[son[u]] <= sum[u] - sum[son[u]]) {
		f[u] = sum[u] / 2;
	} else {
		f[u] = sum[u] - sum[son[u]] + min(f[son[u]], (2 * sum[son[u]] - sum[u]) / 2);
	}
}
int main() {
	scanf("%d%s", &n, s + 1);
	for(int x, y, i = 1; i < n; i ++) {
		scanf("%d%d", &x, &y);
		G[x].push_back(y);
		G[y].push_back(x);
	}
	int ans = -1;
	for(rt = 1; rt <= n; rt ++) {
		dfs(rt);
		if(f[rt] * 2 == sum[rt]) ans = ans == -1 ? f[rt] : min(ans, f[rt]);
	}
	printf("%d\n", ans);
	return 0;
}