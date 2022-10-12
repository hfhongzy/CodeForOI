#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 2010;
const int INF = 2e9 + 10;  
struct Edge {
   int v, w;
};
vector<Edge> G[N];
int n, m, cnt[N], dis[N];
bool inq[N];
bool spfa(int s) {
   fill(cnt + 1, cnt + n + 1, 0);
   fill(inq + 1, inq + n + 1, false);
   fill(dis + 1, dis + n + 1, INF);
   queue<int> q; q.push(s); dis[s] = 0; inq[s] = 1; cnt[s] = 1;
   while(q.size()) {
      int u = q.front(); q.pop(); inq[u] = 0;
      for(auto e : G[u]) if(dis[e.v] > dis[u] + e.w) {
         dis[e.v] = dis[u] + e.w;
         if(!inq[e.v]) {
            inq[e.v] = 1; q.push(e.v);
            if(++ cnt[e.v] >= n) {
               return true;
            }
         }
      }
   }
   return false;
}
int main() {
   int test;
   scanf("%d", &test);
   while(test --) {
      scanf("%d%d", &n, &m);
      rep(i, 1, n) G[i].clear();
      int u, v, w;
      rep(i, 1, m) {
         scanf("%d%d%d", &u, &v, &w);
         G[u].pb({v, w});
         if(w >= 0) G[v].pb({u, w});
      }
      puts(spfa(1) ? "YES" : "NO");
   }
   return 0;
}