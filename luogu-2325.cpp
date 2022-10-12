#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 1e5 + 10;
int n, b, st[N], top, core[N], tot, bel[N];
vector<int> G[N];
void dfs(int u, int fa = 0) {
   int t = top;
   for(int v : G[u]) if(v != fa) {
      dfs(v, u);
      if(top - t >= b) {
         core[++ tot] = u;
         while(t < top) bel[st[top --]] = tot;
      }
   }
   st[++ top] = u;
}
int main() {
   scanf("%d%d", &n, &b);
   rep(i, 1, n - 1) {
      int x, y;
      scanf("%d%d", &x, &y);
      G[x].pb(y); G[y].pb(x);
   }
   dfs(1);
   if(!tot) ++ tot;
   core[tot] = st[top];
   while(top) bel[st[top --]] = tot;
   printf("%d\n", tot);
   rep(i, 1, n) printf("%d%c", bel[i], " \n"[i == n]);
   rep(i, 1, tot) printf("%d%c", core[i], " \n"[i == tot]);
   return 0;
}