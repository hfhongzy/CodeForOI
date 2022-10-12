#include <algorithm>
#include <cstdio>
#include <queue>
#include <cmath>
using namespace std;
typedef long long ll;
const int N = 3020, INF = 2e9 + 10;
int n, sum, a[N], b[N], sz[N];
namespace net {

struct Edge {
	int v, c, f, nxt;
} e[200010];
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
int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}
bool judge(int a, int b) {
	if(gcd(a, b) > 1) return 1;
	ll res = (ll) a * a + (ll) b * b;
	ll x = (ll) (sqrt(res) + 0.2);
	return x * x != res;
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++) scanf("%d", a + i), sum += a[i];
	sort(a + 1, a + n + 1); int nn = 0;
	for(int i = 1; i <= n; i ++) {
		if(a[i] != b[nn]) {
			b[++ nn] = a[i];
		}
		sz[nn] ++;
	}
	n = nn;
	net::n = n + 2; net::init();
	for(int i = 1; i <= n; i ++) if(b[i] & 1) net::add(n + 1, i, b[i] * sz[i]);
	for(int i = 1; i <= n; i ++) if(!(b[i] & 1)) net::add(i, n + 2, b[i] * sz[i]);
	for(int i = 1; i <= n; i ++) if(b[i] & 1)
		for(int j = 1; j <= n; j ++) if(!(b[j] & 1))
			if(!judge(b[i], b[j])) net::add(i, j, INF);
	printf("%d\n", sum - net::dinic());
	return 0;
}