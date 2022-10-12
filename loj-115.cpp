#include <algorithm>
#include <vector>
#include <cstdio>
#include <queue>
using namespace std;

const int N = 210;
const int M = 4e4 + 10;
const int INF = 2e9 + 10;

struct Network {

struct Edge {
   int v, c, f, nxt;
} e[M];
int ec, hd[N], n, s, t;
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
   return ~ dis[n];
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
bool full() {
   for(int i = hd[s]; ~ i; i = e[i].nxt) {
      if(i % 2 == 0 && e[i].f < e[i].c) {
         return 0;
      }
   }
   return 1;
}

} net;
int n, m, b[N], c[M];
int main() {
   scanf("%d%d", &n, &m);
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
   if(net.dinic() != flow) puts("NO");
   else {
      puts("YES");
      for(int i = 0; i < m; i ++) {
         printf("%d\n", net.e[i << 1].f + c[i]);
      }
   }
   return 0;
}