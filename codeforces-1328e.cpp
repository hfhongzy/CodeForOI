#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
const int N = 2e5 + 10;
int n, m, idx, dfn[N], dr[N], f[N];
vector<int> G[N];
void dfs(int u, int fa = 0) {
	dfn[u] = ++ idx; f[u] = fa;
	for(int v : G[u]) if(v ^ fa) {
		dfs(v, u);
	}
	dr[u] = ++ idx;
}
bool cmp(int a, int b) {
	return dfn[a] < dfn[b];
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i < n; i ++) {
		int u, v;
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1);
	vector<int> vec;
	for(int i = 1; i <= m; i ++) {
		int sz; scanf("%d", &sz); vec.clear();
		for(int j = 1; j <= sz; j ++) {
			int x; scanf("%d", &x);
			vec.push_back(f[x] ? f[x] : x);
		}
		sort(vec.begin(), vec.end(), cmp);
		bool suc = 1;
		for(int i = 1; i < sz; i ++) {
			int u = vec[i - 1], v = vec[i];
			if(dfn[u] <= dfn[v] && dfn[v] <= dr[u]) ;
			else { suc = 0; break ; }
		}
		puts(suc ? "YES" : "NO");
	}
	return 0;
}