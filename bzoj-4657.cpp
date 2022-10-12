#include <algorithm>
#include <cstdio>
#include <queue>
using namespace std;
const int INF = 2e9 + 10;
namespace net {

const int N = 5000 + 10;
struct Edge {
	int v, c, f, nxt;
} e[2000010];
int ec, hd[N], n, s, t;
void init() { fill(hd + 1, hd + n + 1, -1); ec = 0; s = n - 1; t = n; }
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
const int N = 55;
int n, m, a[N][N], idx, id[N][N][2];
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++) {
			scanf("%d", &a[i][j]);
			id[i][j][0] = ++ idx;
			id[i][j][1] = ++ idx;
		}
	net::n = idx + 2; net::init();
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			net::add(id[i][j][1], id[i][j][0], INF);
	int ans = 0;
	for(int i = 1; i <= n; i ++) {
		for(int j = 1; j <= m; j ++) if(a[i][j] < 0) {
			int d = - a[i][j] - 1, la = -1, lw = 0, mx = 0; a[i][j] = 0;
			for(int x = i, y = j; 1 <= x && x <= n && 1 <= y && y <= m; x += dx[d], y += dy[d]) {
				mx = max(mx, a[x][y]);
			}
			ans += mx;
			for(int x = i, y = j; 1 <= x && x <= n && 1 <= y && y <= m; x += dx[d], y += dy[d]) {
				int cur = id[x][y][d >> 1];
				if(la == -1) {
					if(d >> 1) net::add(net::s, cur, INF);
					else net::add(cur, net::t, INF);
				} else {
					if(d >> 1) net::add(la, cur, mx - lw);
					else net::add(cur, la, mx - lw);
				}
				la = cur; lw = a[x][y];
			}
			if(d >> 1) net::add(la, net::t, mx - lw);
			else net::add(net::s, la, mx - lw);
		}
	}
	printf("%d\n", ans - net::dinic());
	return 0;
}