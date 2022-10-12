#include <algorithm>
#include <cstdio>
#include <queue>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 110;
const int INF = 2147483647;
namespace net {

const int N = 3e4 + 10, M = 1e6 + 10;
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
int n, m, a[N], d[N][N], idx, ID[N][N], ID2[N * 10];
int main() {
   scanf("%d%d", &n, &m);
   rep(i, 1, n) scanf("%d", a + i);
   rep(i, 1, n) rep(j, i, n) scanf("%d", &d[i][j]), ID[i][j] = ++ idx;
   rep(i, 1, 1000) ID2[i] = ++ idx;
   net::s = idx + 1; net::t = net::n = idx + 2; net::init();
   int sum = 0;
   rep(i, 1, n) rep(j, i, n) {
      int w = 0;
      if(i == j) {
         w = d[i][i] - a[i];
         net::add(ID[i][i], ID2[a[i]], INF);
      } else {
         w = d[i][j];
         net::add(ID[i][j], ID[i + 1][j], INF);
         net::add(ID[i][j], ID[i][j - 1], INF);
      }
      if(w >= 0) net::add(net::s, ID[i][j], w), sum += w;
      else net::add(ID[i][j], net::t, -w);
   }
   rep(i, 1, 1000) {
      int w = m * i * i;
      net::add(ID2[i], net::t, w);
   }
   printf("%d\n", sum - net::dinic());
   return 0;
}