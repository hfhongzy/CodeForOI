#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
namespace Ma {

const int N = 3010;
int n, m, cur, p[N], use[N];
vector<int> G[N];
void clear() {
	for(int i = 1; i <= n; i ++) G[i].clear();
}
bool match(int u) {
	for(int i = 0; i < (int) G[u].size(); i ++) {
		int v = G[u][i];
		if(use[v] == cur) continue ;
		use[v] = cur;
		if(!p[v] || match(p[v])) {
			p[v] = u; return 1;
		}
	}
	return 0;
}
int solve(int res, int ans) {
	fill(p + 1, p + m + 1, 0);
	fill(use + 1, use + m + 1, 0);
	for(cur = 1; cur <= n; cur ++) {
		if(match(cur)) {
			res --;
			if(res <= ans) break ;
		}
	}
	return res;
}

}
const int N = 3030;
int n, m, q, a[N], b[N], t1[N], t2[N], dfn[N];
int L[N], R[N], ls, rs;
vector<int> G[N];
void build() {
	Ma::n = ls; Ma::m = rs; Ma::clear();
	for(int j = 1; j <= ls; j ++)
		for(int k = 1; k <= rs; k ++)
			if(__builtin_popcount(L[j] | R[k]) % 2 == 0)
				Ma::G[j].push_back(k);
}
int main() {
	int test = 1; //scanf("%d", &test);
	while(test --) {
		scanf("%d%d%d", &n, &m, &q);
		for(int i = 1; i <= n; i ++) G[i].clear();
		for(int i = 1; i <= n; i ++) scanf("%d", a + i);
		for(int i = 1; i <= m; i ++) scanf("%d", b + i);
		t1[0] = t2[0] = 0;
		for(int i = 1; i <= n; i ++)
			if(a[i] & 1) t1[++ t1[0]] = i;
			else t2[++ t2[0]] = i;
		for(int i = 1; i <= q; i ++) {
			int u, v;
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
		}
		ls = rs = 0;
		for(int i = 1; i <= m; i ++) {
			if(b[i] & 1) L[++ ls] = b[i];
			else R[++ rs] = b[i];
		}
		build();
		int ans = Ma::solve(m, 0);
		for(int i = 1; i <= n; i ++) {
			ls = rs = 0;
			for(int j = 0; j < (int) G[i].size(); j ++) {
				int v = G[i][j];
				if(b[v] & 1) L[++ ls] = b[v];
				else R[++ rs] = b[v];
			}
			if(ls + rs + 1 <= ans) continue ;
			build(); ans = max(ans, Ma::solve(1 + ls + rs, ans));
		}
		fill(dfn + 1, dfn + t2[0] + 1, 0);
		for(int i = 1; i <= t1[0]; i ++) {
			int u = t1[i];
			for(int j = 0; j < (int) G[u].size(); j ++) {
				int v = G[u][j]; dfn[v] = u;
			}
			for(int j = 1; j <= t2[0]; j ++) {
				int w = t2[j];
				ls = rs = 0;
				for(int k = 0; k < (int) G[w].size(); k ++) {
					int v = G[w][k];
					if(dfn[v] == u) {
						if(b[v] & 1) L[++ ls] = b[v];
						else R[++ rs] = b[v];
					}
				}
				if(ls + rs + 2 <= ans) continue ;
				build(); ans = max(ans, Ma::solve(2 + ls + rs, ans));
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}