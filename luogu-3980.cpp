#include <algorithm>
#include <cstdio>
#include <queue>
using namespace std;
const int N = 1010, M = 16010;
const int INF = 2147483647;
namespace net {

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
               d[e.v] = d[u] + e.w; p[e.v] = i;
               a[e.v] = min(a[u], e.c - e.f);
               if(!inq[e.v]) { q.push(e.v); inq[e.v] = 1; }
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
int n, m, a[N];
int main() {
   scanf("%d%d", &n, &m);
   net::s = 1; net::n = net::t = n + 2; net::init();
   for(int i = 1; i <= n; i ++) scanf("%d", a + i);
   for(int i = 1; i <= n + 1; i ++) net::add(i, i + 1, INF - a[i - 1], 0);
   for(int i = 1; i <= m; i ++) {
      int u, v, c;
      scanf("%d%d%d", &u, &v, &c);
      net::add(u + 1, v + 2, INF, c);
   }
   printf("%d\n", net::mcmf());
   return 0;
}