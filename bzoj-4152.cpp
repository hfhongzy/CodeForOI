#include <algorithm>
#include <vector>
#include <cstdio>
#include <queue>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
const ll INF = 1e18;
namespace G {

const int M = N;
struct Edge { int v, w; };
vector<Edge> G[M];
struct Node {
	int u; ll d;
	bool operator < (const Node &b) const {
		return d > b.d;
	}
};
int n;
void init(int _n) {
	n = _n;
}
void link(int u, int v, int w) {
	G[u].push_back((Edge) {v, w});
}
ll d[M];
void Dijkstra(int s) {
	fill(d + 1, d + n + 1, INF);
	priority_queue<Node> pq; pq.push((Node) {s, d[s] = 0});
	while(pq.size()) {
		int u = pq.top().u; ll du = pq.top().d; pq.pop();
		if(d[u] < du) continue ;
		for(int i = 0; i < (int) G[u].size(); i ++) {
			Edge &e = G[u][i];
			if(d[e.v] > d[u] + e.w) {
				d[e.v] = d[u] + e.w; pq.push((Node) {e.v, d[e.v]});
			}
		}
	}
}

}
struct Node {
	int x, y, id;
} a[N];
int n;
bool cmpx(Node a, Node b) { return a.x < b.x; }
bool cmpy(Node a, Node b) { return a.y < b.y; }
int main() {
	scanf("%d", &n);
	G::init(n);
	for(int i = 1; i <= n; i ++) {
		scanf("%d%d", &a[i].x, &a[i].y); a[i].id = i;
	}
	sort(a + 1, a + n + 1, cmpx);
	for(int i = 2; i <= n; i ++) {
		G::link(a[i - 1].id, a[i].id, a[i].x - a[i - 1].x);
		G::link(a[i].id, a[i - 1].id, a[i].x - a[i - 1].x);
	}
	sort(a + 1, a + n + 1, cmpy);
	for(int i = 2; i <= n; i ++) {
		G::link(a[i - 1].id, a[i].id, a[i].y - a[i - 1].y);
		G::link(a[i].id, a[i - 1].id, a[i].y - a[i - 1].y);
	}
	G::Dijkstra(1);
	printf("%lld\n", G::d[n]);
	return 0;
}