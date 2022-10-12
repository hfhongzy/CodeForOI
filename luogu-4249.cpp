#include <algorithm>
#include <cstdio>
#include <queue>
#define rep(i, j, k) for(int i = j; i <= k; i ++)
#define per(i, j, k) for(int i = j; i >= k; i --)
using namespace std;
namespace net {

const int N = 2e4 + 10, M = 2e4 + 5510;
const int INF = 2147483647;
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
using net::hd;
using net::eg;
const int N = 110;
int n, c, id[N][N], a[N][N], maxF[N];
int main() {
   scanf("%d", &n);
   rep(i, 1, n) rep(j, 1, n) scanf("%d", &a[i][j]);
   rep(i, 1, n) rep(j, i + 1, n) id[i][j] = ++ c;
   net::t = net::n = n + c + 2; net::s = net::n - 1; net::init();
   rep(i, 1, n) rep(j, i + 1, n) {
      net::add(net::s, n + id[i][j], 1, 0);
      if(a[i][j] < 2) {
         net::add(n + id[i][j], !a[i][j] ? i : j, 1, 0);
         maxF[!a[i][j] ? i : j] ++;
      } else {
         net::add(n + id[i][j], i, 1, 0);
         net::add(n + id[i][j], j, 1, 0);
         maxF[i] ++; maxF[j] ++;
      }
   }
   rep(i, 1, n) rep(j, 1, maxF[i]) net::add(i, net::t, 1, j - 1);
   printf("%d\n", n * (n - 1) * (n - 2) / 6 - net::mcmf());
   rep(i, 1, n) rep(j, i + 1, n) {
      int u = n + id[i][j], v = 0;
      for(int e = hd[u]; ~ e; e = eg[e].nxt) if(e % 2 == 0) {
         if(eg[e].f) v = eg[e].v;
      }
      if(v == i) a[i][j] = 0, a[j][i] = 1;
      else a[i][j] = 1, a[j][i] = 0;
   }
   rep(i, 1, n) {
      rep(j, 1, n) printf("%d ", a[i][j]);
      puts("");
   }
   return 0;
}