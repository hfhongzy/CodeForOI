#include <algorithm>
#include <cstdio>
#include <queue>
using namespace std;
const int INF = 2e9 + 10;
namespace net {

const int N = 5010, M = 2e4 + 10;
struct Edge {
   int v, c, f, nxt, add;
} e[M];
int ec, hd[N], n, s, t;
void init() { fill(hd + 1, hd + n + 1, -1); ec = 0; }
void add(int u, int v, int c, int w) {
   e[ec] = (Edge) {v, c, 0, hd[u], w}; hd[u] = ec ++;
   e[ec] = (Edge) {u, 0, 0, hd[v], w}; hd[v] = ec ++;
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
namespace MCMF {

const int N = 5010, M = 2e4 + 10;
struct Edge { int v, c, f, w, nxt; } eg[M * 2];
int n, m, s, t, hd[N], ec;
void init() { fill(hd + 1, hd + n + 1, -1); ec = 0; }
void add(int u, int v, int c, int w) {
   eg[ec] = (Edge) {v, c, 0, w, hd[u]}; hd[u] = ec ++;
   eg[ec] = (Edge) {u, 0, 0, -w, hd[v]}; hd[v] = ec ++;
}
int a[N], p[N], d[N];
bool inq[N];
int mcmf() {
   int ans = 0, cost = 0; queue<int> q;
   while(1) {
      fill(a + 1, a + n + 1, 0); a[s] = INF;
      fill(d + 1, d + n + 1, INF); d[s] = 0;
      q.push(s); inq[s] = 0;
      while(q.size()) {
         int u = q.front(); q.pop(); inq[u] = 0;
         for(int i = hd[u]; ~ i; i = eg[i].nxt) {
            Edge &e = eg[i];
            if(d[e.v] > d[u] + e.w && e.c > e.f) {
               d[e.v] = d[u] + e.w;
               a[e.v] = min(a[u], e.c - e.f);
               p[e.v] = i;
               if(!inq[e.v]) {
                  q.push(e.v);
                  inq[e.v] = 1;
               }
            }
         }
      }
      if(d[t] == INF) break ;
      ans += a[t]; cost += a[t] * d[t];
      for(int u = t; u != s; u = eg[p[u] ^ 1].v) {
         eg[p[u]].f += a[t]; eg[p[u] ^ 1].f -= a[t];
      }
   }
   return cost;
}

}
int n, m, k;
int main() {
   scanf("%d%d%d", &n, &m, &k);
   net::s = 1; net::t = net::n = n; net::init();
   for(int i = 1; i <= m; i ++) {
      int u, v, c, w;
      scanf("%d%d%d%d", &u, &v, &c, &w);
      net::add(u, v, c, w);
   }
   printf("%d ", net::dinic());
   MCMF::s = 1; MCMF::t = MCMF::n = n + 1; MCMF::init();
   MCMF::add(n, n + 1, k, 0);
   net::Edge *e = net::e;
   for(int i = 0; i < net::ec; i ++) {
      MCMF::add(e[i ^ 1].v, e[i].v, e[i].c - e[i].f, 0);
      if(!(i & 1)) MCMF::add(e[i ^ 1].v, e[i].v, INF, e[i].add);
   }
   printf("%d\n", MCMF::mcmf());
   return 0;
}