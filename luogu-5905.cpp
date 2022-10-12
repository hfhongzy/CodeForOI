#include <algorithm>
#include <cstdio>
#include <queue>
using namespace std;

const int N = 3e3 + 10, M = 6e4 + 10;
const int INF = 1e9;
int n, m;
struct Node {
   int u, d;
   bool operator < (const Node &b) const { return d > b.d; }
};
struct Edge { int v, w, nxt; };
struct Graph {

Edge eg[M];
int hd[N], ec;
void init() { fill(hd + 1, hd + n + 2, -1); ec = 0; }
void add(int u, int v, int w) {
   eg[ec] = (Edge) {v, w, hd[u]}; hd[u] = ec ++;
}
bool inq[N];
int d[N], cnt[N];
bool spfa(int s) {
   queue<int> q; q.push(s); inq[s] = 1;
   fill(d + 1, d + n + 2, INF); d[s] = 0;
   fill(cnt + 1, cnt + n + 2, 0);
   while(q.size()) {
      int u = q.front(); q.pop(); inq[u] = 0;
      if(++ cnt[u] >= n) {
         return false;
      }
      for(int i = hd[u]; ~ i; i = eg[i].nxt) {
         Edge &e = eg[i];
         if(d[e.v] > d[u] + e.w) {
            d[e.v] = d[u] + e.w;
            if(!inq[e.v]) {
               q.push(e.v);
               inq[e.v] = 1;
            }
         }
      }
   }
   return true;
}
void Dijkstra(int s) {
   fill(d + 1, d + n + 2, INF);
   priority_queue<Node> pq; pq.push((Node) {s, d[s] = 0});
   while(pq.size()) {
      int u = pq.top().u, du = pq.top().d; pq.pop();
      if(d[u] < du) continue ;
      for(int i = hd[u]; ~ i; i = eg[i].nxt) {
         Edge &e = eg[i];
         if(d[e.v] > d[u] + e.w) {
            pq.push((Node) {e.v, d[e.v] = d[u] + e.w});
         }
      }
   }
}

} G1, G2;
int main() {
   static int eu[M], ev[M], ew[M];
   scanf("%d%d", &n, &m); G1.init(); G2.init();
   int u, v, w;
   for(int i = 1; i <= n; i ++) G1.add(n + 1, i, 0);
   for(int i = 1; i <= m; i ++) {
      scanf("%d%d%d", &u, &v, &w);
      G1.add(v, u, w);
      eu[i] = u; ev[i] = v; ew[i] = w;
   }
   if(!G1.spfa(n + 1)) {
      puts("-1"); return 0;
   }
   for(int i = 1; i <= m; i ++) {
      G2.add(eu[i], ev[i], ew[i] - G1.d[eu[i]] + G1.d[ev[i]]);
   }
   for(int i = 1; i <= n; i ++) {
      G2.Dijkstra(i);
      long long res = 0;
      for(int j = 1; j <= n; j ++) {
         if(G2.d[j] == INF) res += 1ll * j * INF;
         else res += 1ll * j * (G2.d[j] - G1.d[j] + G1.d[i]);
      }
      printf("%lld\n", res);
   }
   return 0;
}