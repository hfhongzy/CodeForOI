#include <bits/stdc++.h>
#define fs first
#define sc second
#define pb push_back
#define pii pair<int, int>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 1e4 + 10;
int n, m, w[N], dfn[N], low[N], idx, bel[N], val[N], d[N], dp[N], scc;
vector<int> G[N], T[N];
stack<int> st;
bool ins[N];
void tarjan(int u) {
   dfn[u] = low[u] = ++ idx; st.push(u); ins[u] = 1;
   for(int v : G[u]) {
      if(!dfn[v]) {
         tarjan(v);
         low[u] = min(low[u], low[v]);
      } else if(ins[v]) {
         low[u] = min(low[u], dfn[v]);
      }
   }
   if(low[u] == dfn[u]) {
      int v = 0; scc ++;
      do {
         v = st.top(); st.pop(); ins[v] = 0;
         bel[v] = scc; val[scc] += w[v];
      } while(v != u);
   }
}
int main() {
   scanf("%d%d", &n, &m);
   rep(i, 1, n) scanf("%d", w + i);
   int u, v;
   rep(i, 1, m) {
      scanf("%d%d", &u, &v); G[u].pb(v);
   }
   rep(i, 1, n) if(!dfn[i]) tarjan(i);
   rep(i, 1, n) for(int v : G[i]) {
      if(bel[v] != bel[i]) {
         T[bel[i]].pb(bel[v]); d[bel[v]] ++;
      }
   }
   queue<int> q;
   rep(i, 1, scc) if(!d[i]) q.push(i), dp[i] = val[i];
   while(q.size()) {
      int u = q.front(); q.pop();
      for(int v : T[u]) {
         dp[v] = max(dp[v], dp[u] + val[v]);
         if(! -- d[v]) q.push(v);
      }
   }
   printf("%d\n", *max_element(dp + 1, dp + scc + 1));
   return 0;
}