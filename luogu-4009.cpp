#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 2e5 + 10, S = 110, INF = 2e9 + 7;
struct Edge { int v, w; };
struct Graph {
   vector<Edge> G[N];
   void add(int u, int v, int w) {
      G[u].push_back({v, w});
   }
   struct Node {
      int u, d;
      bool operator < (const Node &b) const {
         return d > b.d;
      }
   };
   int dis[N];
   void Dijkstra(int s, int n) {
      fill(dis + 1, dis + n + 1, INF);
      priority_queue<Node> pq; pq.push({s, dis[s] = 0});
      while(pq.size()) {
         int u = pq.top().u, d = pq.top().d; pq.pop();
         if(dis[u] < d) continue ;
         for(auto e : G[u]) if(dis[e.v] > d + e.w) {
            dis[e.v] = d + e.w; pq.push({e.v, dis[e.v]});
         }
      }
   }
} G;
int n, k, a, b, c, tag[S][S];
int ID(int h, int x, int y) { return (x - 1) * n + y + h * n * n; }
int main() {
   scanf("%d%d%d%d%d", &n, &k, &a, &b, &c);
   rep(i, 1, n) rep(j, 1, n) scanf("%d", tag[i] + j);
   rep(i, 1, n) rep(j, 1, n) {
      if(i != n) {
         if(tag[i + 1][j]) rep(h, 0, k - 1) G.add(ID(h, i, j), ID(0, i + 1, j), a);
         else {
            rep(h, 0, k - 1) G.add(ID(h, i, j), ID(h + 1, i + 1, j), 0);
            rep(h, 0, k - 1) G.add(ID(h, i, j), ID(0, i + 1, j), a + c);
         }
         if(tag[i][j]) rep(h, 0, k - 1) G.add(ID(h, i + 1, j), ID(0, i, j), a + b);
         else {
            rep(h, 0, k - 1) G.add(ID(h, i + 1, j), ID(h + 1, i, j), b);
            rep(h, 0, k - 1) G.add(ID(h, i + 1, j), ID(0, i, j), a + b + c);
         }
      }
      if(j != n) {
         if(tag[i][j + 1]) rep(h, 0, k - 1) G.add(ID(h, i, j), ID(0, i, j + 1), a);
         else {
            rep(h, 0, k - 1) G.add(ID(h, i, j), ID(h + 1, i, j + 1), 0);
            rep(h, 0, k - 1) G.add(ID(h, i, j), ID(0, i, j + 1), a + c);
         }
         if(tag[i][j]) rep(h, 0, k - 1) G.add(ID(h, i, j + 1), ID(0, i, j), a + b);
         else {
            rep(h, 0, k - 1) G.add(ID(h, i, j + 1), ID(h + 1, i, j), b);
            rep(h, 0, k - 1) G.add(ID(h, i, j + 1), ID(0, i, j), a + b + c);
         }
      }
   }
   G.Dijkstra(ID(0, 1, 1), (k + 1) * n * n);
   int ans = INF;
   rep(h, 0, k) ans = min(ans, G.dis[ID(h, n, n)]);
   printf("%d\n", ans);
   return (int)0.0;
}