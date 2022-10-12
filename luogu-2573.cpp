#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>
#define fs first
#define sc second
#define pb push_back
#define pii pair<int, int>
using namespace std;

const int N = 1e5 + 10;
int n, m, h[N], d[N];
bool mark[N];
vector<pii> G[N];
struct cmp {
	bool operator () (pii x, pii y) const {
		if(h[x.sc] ^ h[y.sc]) return h[x.sc] < h[y.sc];
		return x > y;
	}
};
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++) scanf("%d", h + i);
	for(int i = 1; i <= m; i ++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		G[u].pb(pii(v, w)); G[v].pb(pii(u, w));
	}
	long long cnt = 0, ans = 0;
	fill(d + 1, d + n + 1, (int) 2e9);
	priority_queue< pii, vector<pii>, cmp > pq;
	pq.push(pii(0, 1)); d[1] = 0;
	while(pq.size()) {
		int u = pq.top().sc, dd = pq.top().fs; pq.pop();
		if(mark[u]) continue ;
		mark[u] = 1; ans += dd; cnt ++; d[u] = 0;
		for(int i = 0; i < (int) G[u].size(); i ++) {
			int &v = G[u][i].fs, &w = G[u][i].sc;
			if(!mark[v] && d[v] > w && h[v] <= h[u]) {
				pq.push(pii(d[v] = w, v));
			}
		}
	}
	printf("%d %lld\n", (int) cnt, ans);
	return 0;
}