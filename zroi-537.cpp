#include <algorithm>
#include <cstdio>
#include <queue>
using namespace std;
const int N = 1210, M = N * N * 2, INF = 1e9 + 10;
struct Node {
   int l, r;
   bool operator < (const Node &b) const {
      return l < b.l || (l == b.l && r < b.r);
   }
} a[N];
int m, n;
namespace net {

int n, s, t;
struct Edge { int v, c, f, nxt; } e[M];
int hd[N], p;
void clr() {
   fill(hd + 1, hd + n + 1, -1); p = 0;
}
void add(int u, int v, int c) {
   e[p] = (Edge) {v, c, 0, hd[u]}; hd[u] = p ++;
   e[p] = (Edge) {u, 0, 0, hd[v]}; hd[v] = p ++;
}

queue<int> q;
int d[N], cur[N];
bool bfs() {
   fill(d + 1, d + n + 1, -1);
   q.push(s); d[s] = 0;
   while(!q.empty()) {
      int u = q.front(); q.pop();
      for(int i = hd[u]; ~ i; i = e[i].nxt) {
         int v = e[i].v; 
         if(d[v] == -1 && e[i].c > e[i].f) {
            d[v] = d[u] + 1; q.push(v);
         }
      }
   }
   return ~ d[t];
}
int dfs(int u, int a) {
   if(u == t || a == 0) return a;
   int ans = 0, f;
   for(int &i = cur[u]; ~ i; i = e[i].nxt) {
      int v = e[i].v;
      if(d[u] + 1 == d[v] && (f = dfs(v, min(a, e[i].c - e[i].f))) > 0) {
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
int main() {
   scanf("%d%d", &n, &m);
   for(int i = 1; i <= n; i ++) scanf("%d%d", &a[i].l, &a[i].r);
   net::t = net::n = n + 2 * 400 + 2; net::s = net::t - 1; net::clr();
   for(int i = 1; i <= m; i ++) {
      net::add(net::s, i, 1);
      for(int j = a[i].l; j <= a[i].r; j ++)
         net::add(i, n + j, INF);
   }
   for(int i = m + 1; i <= n; i ++) {
      net::add(i, net::t, 1);
      for(int j = a[i].l; j <= a[i].r; j ++)
         net::add(n + 400 + j, i, INF);
   }
   for(int i = 1; i <= 400; i ++) net::add(n + i, n + 400 + i, 1);
   int ans = 0;
   sort(a + 1, a + n + 1);
   int p = 1;
   priority_queue< int, vector<int>, greater<int> > pq;
   for(int i = 1; i <= 400; i ++) {
      for(; p <= n && a[p].l <= i; p ++) {
         pq.push(a[p].r);
      }
      while(pq.size() && pq.top() < i) pq.pop();
      if(pq.size()) {
         pq.pop(); ans ++;
      }
   }
   printf("%d\n%d\n", ans, net::dinic());
   return 0;
}