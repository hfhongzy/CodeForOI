#include <algorithm>
#include <cstdio>
#include <queue>
using namespace std;
const int INF = 2e9 + 10;
namespace net {

const int N = 64010;
struct Edge {
	int v, c, f, nxt;
} e[N * 8];
int ec, hd[N], n;
void init() {
	fill(hd + 1, hd + n + 1, -1); ec = 0;
}
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
const int N = 42;
int n, m, h, d, id[N][N][N], val[N][N][N], cur;
int main() {
	scanf("%d%d%d%d", &n, &m, &h, &d);
	for(int i = 1; i <= h; i ++) {
		for(int j = 1; j <= n; j ++) {
			for(int k = 1; k <= m; k ++) {
				scanf("%d", &val[j][k][i]);
				id[j][k][i] = ++ cur;
			}
		}
	}
	net::n = cur + 2; net::init();
	const int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
	for(int x = 1; x <= n; x ++) {
		for(int y = 1; y <= m; y ++) {
			for(int z = 1; z <= h; z ++) {
				if(z == 1) net::add(net::n - 1, id[x][y][1], val[x][y][z]);
				else net::add(id[x][y][z - 1], id[x][y][z], val[x][y][z]);
				if(z == h) net::add(id[x][y][h], net::n, INF);
				if(z <= d + 1) continue ;
				for(int u = 0; u < 4; u ++) {
					int nx = x + dx[u], ny = y + dy[u];
					if(nx >= 1 && ny >= 1 && nx <= n && ny <= m) {
						net::add(id[x][y][z - 1], id[nx][ny][z - d - 1], INF);
					}
				}
			}
			
		}
	}
	printf("%d\n", net::dinic());
	return 0;
}