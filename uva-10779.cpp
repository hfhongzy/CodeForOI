#include <algorithm>
#include <cstdio>
#include <queue>
#include <stack>
using namespace std;
const int INF = 2e9 + 10;
const int N = 6e4 + 10;
struct Edge {
   int v, c, f, nxt;
} e[N * 10];
int ec, hd[N], n, m, s, t;
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
bool viss[N], vist[N];
void dfss(int u) {
   viss[u] = 1;
   for(int i = hd[u]; ~ i; i = e[i].nxt) {
      if(e[i].c > e[i].f && !viss[e[i].v]) {
         dfss(e[i].v);
      }
   }
}
void dfst(int u) {
   vist[u] = 1;
   for(int i = hd[u]; ~ i; i = e[i].nxt) {
      if(e[i ^ 1].c > e[i ^ 1].f && !vist[e[i].v] && !viss[e[i].v]) {
         dfst(e[i].v);
      }
   }
}
int main() {
   scanf("%d%d%d%d", &n, &m, &s, &t); init();
   for(int u, v, w, i = 1; i <= m; i ++) {
      scanf("%d%d%d", &u, &v, &w);
      add(u, v, w);
   }
   return 0;
}