#include <algorithm>
#include <cstdio>
#include <queue>
using namespace std;
const int INF = 2e9 + 10;
namespace net {

const int N = 70010, M = 2e6 + 10;
struct Edge {
   int v, c, f, nxt;
} e[M];
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
const int N = 105;
int n, m, a1[N][N], a2[N][N], d1[N][N], d2[N][N], r1[N][N], r2[N][N], sum;
void RdArray(int a[N][N], int n, int m) {
   for(int i = 1; i <= n; i ++) {
      for(int j = 1; j <= m; j ++) {
         scanf("%d", &a[i][j]);
         sum += a[i][j];
      }
   }
}
int ID(int m, int x, int y) { return (x - 1) * m + y; }
int main() {
   scanf("%d%d", &n, &m);
   RdArray(a1, n, m); RdArray(a2, n, m);
   RdArray(d1, n - 1, m); RdArray(d2, n - 1, m);
   RdArray(r1, n, m - 1); RdArray(r2, n, m - 1);
   net::n = n * m + 2 * (n - 1) * m + 2 * n * (m - 1) + 2;
   net::s = net::n - 1; net::t = net::n;
   net::init();
   const int I2 = n * m, I3 = I2 + (n - 1) * m, I4 = I3 + (n - 1) * m, I5 = I4 + n * (m - 1);
   for(int i = 1; i <= n; i ++) {
      for(int j = 1; j <= m; j ++) {
         net::add(net::s, ID(m, i, j), a1[i][j]);
         net::add(ID(m, i, j), net::t, a2[i][j]);

         if(i <= n - 1) {
            int x = I2 + ID(m, i, j);
            net::add(net::s, x, d1[i][j]);
            net::add(x, ID(m, i, j), INF);
            net::add(x, ID(m, i + 1, j), INF);

            x = I3 + ID(m, i, j);
            net::add(x, net::t, d2[i][j]);
            net::add(ID(m, i, j), x, INF);
            net::add(ID(m, i + 1, j), x, INF);
         }
         if(j <= m - 1) {
            int x = I4 + ID(m - 1, i, j);
            net::add(net::s, x, r1[i][j]);
            net::add(x, ID(m, i, j), INF);
            net::add(x, ID(m, i, j + 1), INF);

            x = I5 + ID(m - 1, i, j);
            net::add(x, net::t, r2[i][j]);
            net::add(ID(m, i, j), x, INF);
            net::add(ID(m, i, j + 1), x, INF);
         }
      }
   }

   printf("%d\n", sum - net::dinic());
   return 0;
}