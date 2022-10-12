#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 2e6 + 10;
int n, m, scc, dfn[N], low[N], bel[N]; //[1, n] : true
vector<int> G[N];
stack<int> st;
bool ins[N];
void tarjan(int u) {
   low[u] = dfn[u] = ++ *dfn; st.push(u); ins[u] = 1;
   for(int v : G[u]) {
      if(!dfn[v]) {
         tarjan(v);
         low[u] = min(low[u], low[v]);
      } if(ins[v]) {
         low[u] = min(low[u], dfn[v]);
      }
   }
   if(dfn[u] == low[u]) {
      int v = 0; scc ++;
      do {
         v = st.top(); st.pop(); ins[v] = 0;
         bel[v] = scc;
      } while(v != u);
   }
}
int main() {
   scanf("%d%d", &n, &m);
   int u, wu, v, wv;
   rep(i, 1, m) {
      scanf("%d%d%d%d", &u, &wu, &v, &wv);
      int x[2] = {wu ? u : u + n, wu ? u + n : u};
      int y[2] = {wv ? v : v + n, wv ? v + n : v};
      G[x[1]].pb(y[0]); G[y[1]].pb(x[0]);
   }
   rep(i, 1, 2 * n) if(!dfn[i]) tarjan(i);
   rep(i, 1, n) if(bel[i] == bel[i + n]) puts("IMPOSSIBLE"), exit(0);
   puts("POSSIBLE");
   rep(i, 1, n) printf("%d%c", (int)(bel[i] < bel[i + n]), " \n"[i == n]);
   return 0;
}