#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
const int N = 1010;
int n, m, p[N];
bool use[N];
vector<int> G[N];
bool match(int u) {
	for(int i = 0; i < (int) G[u].size(); i ++) {
		int v = G[u][i];
		if(use[v]) continue ;
		use[v] = 1;
		if(!p[v] || match(p[v])) {
			p[v] = u; return 1;
		}
	}
	return 0;
}
int main() {
	scanf("%d%d", &n, &m);
	int e; scanf("%d", &e);
	while(e --) {
		int u, v;
		scanf("%d%d", &u, &v);
		if(u <= n && v <= m)
			G[u].push_back(v);
	}
	int ans = 0;
	for(int i = 1; i <= n; i ++) {
		fill(use + 1, use + m + 1, 0);
		if(match(i)) ans ++;
	}
	printf("%d\n", ans);
	return 0;
}