#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 512;
int n, m, e, a[N];
bool G[N][N], vis[N];
bool dfs(int u) {
   rep(v, 1, m) if(G[u][v]) {
      if(vis[v]) continue ;
      vis[v] = 1;
      if(!a[v] || dfs(a[v])) {
         a[v] = u; return 1;
      }
   }
   return 0;
}
int main() {
   scanf("%d%d%d", &n, &m, &e);
   int u, v;
   rep(i, 1, e) {
      scanf("%d%d", &u, &v);
      if(u <= n && v <= m) G[u][v] = 1;
   }
   int ans = 0;
   rep(i, 1, n) {
      fill(vis + 1, vis + m + 1, 0);
      ans += dfs(i);
   }
   printf("%d\n", ans);
   return 0;
}