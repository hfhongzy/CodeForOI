#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
int n, k, d, p[N], f[N], g[N], tot[N];
vector<int> G[N], cnt[N];
void dfs(int u, int fa = 0) {
   p[u] = fa;
   for(int v : G[u]) if(v != fa) {
      dfs(v, u); f[v] ++;
      if(f[v] > f[u]) {
         g[u] = f[u]; f[u] = f[v];
      } else if(f[v] > g[u]) {
         g[u] = f[v];
      }
   }
   d = max(d, f[u] + g[u]);
}
int main() {
   scanf("%d%d", &n, &k);
   int u, v;
   rep(i, 1, n - 1) {
      scanf("%d%d", &u, &v);
      G[u].pb(v); G[v].pb(u);
   }
   dfs(1);
   rep(i, 1, n) cnt[i].resize(d + 1);
   rep(i, 1, n) {
      int tmp = k;
      fill(tot, tot + d + 1, 0); tot[0] = 1;
      for(int u = i; u; u = p[u]) {
         rep(j, 1, d) {
            tot
         }
      }
      rep(j, 0, d) if((tmp -= tot[j]) <= 0) break ;
      
   }
   return 0;
}