#include <algorithm>
#include <vector>
#include <cstdio>
#include <queue>
using namespace std;

const int N = 5e4 + 10;
const int M = 125003 * 4 + 10;
const int INF = 2147483647;

struct Network {

struct Edge {
   int v, c, f, nxt;
} e[M];
int ec, hd[N], n, s, t, real_s, real_t;
void init() { fill(hd + 1, hd + n + 1, -1); ec = 0; }
void add(int u, int v, int c) {
   e[ec] = (Edge) {v, c, 0, hd[u]}; hd[u] = ec ++;
   e[ec] = (Edge) {u, 0, 0, hd[v]}; hd[v] = ec ++;
}
int dis[N], cur[N];
bool bfs() {
   fill(dis + 1, dis + n + 1, -1);
   queue<int> q; q.push(real_s); dis[real_s] = 0;
   while(q.size()) {
      int u = q.front(); q.pop();
      for(int i = hd[u]; ~ i; i = e[i].nxt) {
         int v = e[i].v;
         if(e[i].f < e[i].c && -1 == dis[v]) {
            dis[v] = dis[u] + 1; q.push(v);
         }
      }
   }
   return ~ dis[real_t];
}
int dfs(int u, int a) {
   if(u == real_t || a == 0) return a;
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
int dinic(int s, int t) {
   real_s = s; real_t = t; int ans = 0;
   while(bfs()) {
      copy(hd + 1, hd + n + 1, cur + 1);
      ans += dfs(real_s, INF);
   }
   return ans;
}

} net;
int n, m, s, t, b[N], c[M];
int main() {
   scanf("%d%d%d%d", &n, &m, &s, &t);
   net.n = net.t = n + 2; net.s = n + 1; net.init();
   for(int u, v, l, r, i = 1; i <= m; i ++) {
      scanf("%d%d%d%d", &u, &v, &l, &r); c[i - 1] = l;
      net.add(u, v, r - l); b[u] -= l; b[v] += l;
   }
   int flow = 0;
   for(int i = 1; i <= n; i ++) {
      if(b[i] > 0) net.add(net.s, i, b[i]), flow += b[i];
      if(b[i] < 0) net.add(i, net.t, -b[i]);
   }
   net.add(t, s, INF);
   if(net.dinic(net.s, net.t) != flow) puts("please go home to sleep");
   else {
      int ans = net.e[net.ec - 2].f;
      net.e[net.ec - 2].f = net.e[net.ec - 2].c = 0;
      net.e[net.ec - 1].f = net.e[net.ec - 1].c = 0;
      ans -= net.dinic(t, s);
      printf("%d\n", ans);
   }
   return 0;
}