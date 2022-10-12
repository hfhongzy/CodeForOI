#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 1005;
int n, rk[N][N], d[N][N];
vector<int> G[N];
void bfs(int s) {
   int *dis = d[s], *seq = rk[s], cnt = 0;
   fill(dis + 1, dis + n + 1, -1);
   queue<int> q; q.push(s); dis[s] = 0;
   while(q.size()) {
      int u = q.front(); q.pop(); seq[++ cnt] = u;
      for(int v : G[u]) if(-1 == dis[v]) {
         dis[v] = dis[u] + 1; q.push(v);
      }
   }
}
int main() {
   int test; scanf("%d", &test);
   while(test --) {
      scanf("%d", &n);
      int u, c, v;
      rep(i, 1, n) {
         scanf("%d%d", &u, &c);
         G[u].clear();
         rep(j, 1, c) {
            scanf("%d", &v);
            G[u].pb(v);
         }
      }
      rep(i, 1, n) bfs(i);
      const int w = 1;
      int ans = n;
      rep(i, 1, n) ans = min(ans, 2 * d[rk[i][n]][i]);
      rep(u, 1, n) for(int v : G[u]) if(u < v) {
         int p = n;
         for(int i = n - 1; i >= 1; i --) {
            if(d[v][rk[u][p]] < d[v][rk[u][i]]) {
               ans = min(ans, d[u][rk[u][i]] + d[v][rk[u][p]] + w);
               p = i;
            }
         }
      }
      printf("%d\n", ans);
   }
   return 0;
}