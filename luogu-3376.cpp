#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int INF = INT_MAX;

namespace net {

const int N = 510, M = 4e5 + 10;
struct Edge {
   int v, c, f, nxt;
} e[M];
int ec, hd[N], n, s, t;
void init(int _n) {
   n = _n; fill(hd + 1, hd + n + 1, -1); ec = 0;
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
ll dinic() {
   ll ans = 0;
   while(bfs()) {
      copy(hd + 1, hd + n + 1, cur + 1);
      ans += dfs(s, INF);
   }
   return ans;
}

}
int main() {
   int n, m, s, t;
   scanf("%d%d%d%d", &n, &m, &s, &t);
   net::init(n); net::s = s; net::t = t;
   for(int u, v, w, i = 1; i <= m; i ++) {
      scanf("%d%d%d", &u, &v, &w);
      net::add(u, v, w);
   }
   printf("%lld\n", net::dinic());
   return 0;
}