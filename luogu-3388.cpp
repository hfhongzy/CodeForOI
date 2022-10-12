#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 2e4 + 10;
int n, m, dfn[N], low[N], idx;
vector<int> G[N];
bool cut[N];
void tarjan(int u, int fa = 0) {
   dfn[u] = low[u] = ++ idx;
   int ch = 0;
   for(int v : G[u]) {
      if(!dfn[v]) {
         tarjan(v, u);
         low[u] = min(low[u], low[v]);
         if(low[v] >= dfn[u]) {
            ch ++;
         }
      } else if(v != fa) {
         low[u] = min(low[u], dfn[v]);
      }
   }
   if(!fa && ch >= 2 || fa && ch >= 1) cut[u] = 1;
}
int main() {
   scanf("%d%d", &n, &m);
   int u, v;
   rep(i, 1, m) {
      scanf("%d%d", &u, &v);
      G[u].pb(v); G[v].pb(u);
   }
   rep(i, 1, n) if(!dfn[i]) tarjan(i);
   int s = 0;
   rep(i, 1, n) s += cut[i];
   printf("%d\n", s);
   rep(i, 1, n) if(cut[i]) {
      printf("%d ", i);
   }
   return 0;
}