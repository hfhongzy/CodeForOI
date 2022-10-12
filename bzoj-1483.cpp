#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
const int N = 1e6 + 5;
int n, m, ans, a[N], bel[N];
vector<int> pos[N];
void merge(int u, int v) {
	for(int i = 0; i < (int) pos[u].size(); i ++) {
		int p = pos[u][i]; ans -= (a[p - 1] == v) + (a[p + 1] == v);
		pos[v].push_back(p);
 	}
 	for(int i = 0; i < (int) pos[u].size(); i ++) a[pos[u][i]] = v;
 	pos[u].clear();
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++) {
		scanf("%d", a + i);
		int t = a[i]; bel[t] = t;
		ans += a[i] != a[i - 1];
		pos[t].push_back(i);
	}
	for(int i = 1; i <= m; i ++) {
		int op, u, v;
		scanf("%d", &op);
		if(op == 1) {
			scanf("%d%d", &u, &v);
			if(v != u) {
				if(pos[bel[u]].size() > pos[bel[v]].size()) swap(bel[u], bel[v]);
				merge(bel[u], bel[v]);
			}
		}
		if(op == 2) printf("%d\n", ans);
	}
	return 0;
}