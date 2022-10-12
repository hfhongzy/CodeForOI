#include <algorithm>
#include <cstdio>
#include <queue>
using namespace std;
const int INF = 2e9 + 10;
namespace net {

const int N = 30010;
struct Edge {
	int v, c, f, nxt;
} e[N * 200];
int ec, hd[N], n;
void init() { fill(hd + 1, hd + n + 1, -1); ec = 0; }
void add(int u, int v, int c) {
	e[ec] = (Edge) {v, c, 0, hd[u]}; hd[u] = ec ++;
	e[ec] = (Edge) {u, 0, 0, hd[v]}; hd[v] = ec ++;
}
int dis[N], cur[N];
bool bfs() {
	fill(dis + 1, dis + n + 1, -1);
	queue<int> q; q.push(n - 1); dis[n - 1] = 0;
	while(q.size()) {
		int u = q.front(); q.pop();
		for(int i = hd[u]; ~ i; i = e[i].nxt) {
			int v = e[i].v;
			if(e[i].f < e[i].c && -1 == dis[v]) {
				dis[v] = dis[u] + 1; q.push(v);
			}
		}
	}
	return ~ dis[n];
}
int dfs(int u, int a) {
	if(u == n || a == 0) return a;
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
		ans += dfs(n - 1, INF);
	}
	return ans;
}

}
const int N = 105;
int n, m, a[N][N], b[N][N], sa[N][N], sb[N][N], sum;
void RdArray(int a[N][N]) {
	for(int i = 1; i <= n; i ++) {
		for(int j = 1; j <= m; j ++) {
			scanf("%d", &a[i][j]);
			sum += a[i][j];
		}
	}
}
int id(int x, int y) {
	return (x - 1) * m + y;
}
int main() {
	scanf("%d%d", &n, &m);
	RdArray(a); RdArray(b); RdArray(sa); RdArray(sb);
	net::n = 3 * n * m + 2; net::init();
	const int dx[] = {1, 0, -1, 0, 0};
	const int dy[] = {0, 1, 0, -1, 0};
	for(int i = 1; i <= n; i ++) {
		for(int j = 1; j <= m; j ++) {
			net::add(net::n - 1, id(i, j), a[i][j]);
			net::add(id(i, j), net::n, b[i][j]);
			net::add(net::n - 1, n * m + id(i, j), sa[i][j]);
			net::add(2 * n * m + id(i, j), net::n, sb[i][j]);
			for(int d = 0; d < 5; d ++) {
				int nx = i + dx[d], ny = j + dy[d];
				if(nx >= 1 && ny >= 1 && nx <= n && ny <= m) {
					net::add(n * m + id(i, j), id(nx, ny), INF);
					net::add(id(nx, ny), 2 * n * m + id(i, j), INF);
				}
			}
		}
	}
	printf("%d\n", sum - net::dinic());
	return 0;
}