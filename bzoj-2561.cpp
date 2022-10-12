#include <algorithm>
#include <cstdio>
#include <queue>
using namespace std;
const int INF = 2e9 + 10;
namespace net {

const int N = 2e5 + 10;
struct Edge {
	int v, c, f, nxt;
} e[N * 10];
int ec, hd[N], n, s, t;
void init() { fill(hd + 1, hd + n + 1, -1); ec = 0; }
void add(int u, int v, int c) {
	e[ec] = (Edge) {v, c, 0, hd[u]}; hd[u] = ec ++;
	e[ec] = (Edge) {u, 0, 0, hd[v]}; hd[v] = ec ++;
}
int dis[N], cur[N];
bool bfs() {
	fill(dis + 1, dis + n + 1, -1);
	queue<int> q; q.push(s); dis[s] = 0;
	while(q.size()) {
		int u = q.front(); q.pop();
		for(int i = hd[u]; ~ i; i = e[i].nxt) {
			int v = e[i].v;
			if(e[i].f < e[i].c && -1 == dis[v]) {
				dis[v] = dis[u] + 1; q.push(v);
			}
		}
	}
	return ~ dis[t];
}
int dfs(int u, int a) {
	if(u == t || a == 0) return a;
	int ans = 0, f;
	for(int &i = cur[u]; ~ i; i = e[i].nxt) {
		int v = e[i].v;
		if(dis[v] == dis[u] + 1 && (f = dfs(v, min(a, e[i].c - e[i].f))) > 0) {
			ans += f; e[i].f += f; e[i ^ 1].f -= f;
			if((a -= f) == 0) break ;
		}
	}
	return ans;
}
int dinic() {
	int ans = 0;
	while(bfs()) {
		copy(hd + 1, hd + n + 1, cur + 1);
		ans += dfs(s, INF);
	}
	return ans;
}

}
const int N = 2e5 + 10;
int n, m, u[N], v[N], w[N];
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m + 1; i ++)
		scanf("%d%d%d", u + i, v + i, w + i);
	net::s = u[m + 1]; net::t = v[m + 1];
	net::n = n + 2; net::init();
	for(int i = 1; i <= m; i ++) {
		if(w[i] < w[m + 1]) {
			net::add(u[i], v[i], 1);
			net::add(v[i], u[i], 1);
		}
	}
	int ans = net::dinic();
	net::n = n + 2; net::init();
	for(int i = 1; i <= m; i ++) {
		if(w[i] > w[m + 1]) {
			net::add(u[i], v[i], 1);
			net::add(v[i], u[i], 1);
		}
	}
	printf("%d\n", ans + net::dinic());
	return 0;
}