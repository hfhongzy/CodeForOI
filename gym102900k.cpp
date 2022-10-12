#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 4e5 + 10;
int n, m, id;
int dfn[N], dr[N], low[N], st[N], top, idx, f[N];
char s[N];
vector<int> G[N], T[N];
void tarjan(int u) {
  st[++ top] = u; low[u] = dfn[u] = ++ idx;
  for(int v : G[u]) {
    if(!dfn[v]) {
      tarjan(v); low[u] = min(low[u], low[v]);
      if(low[v] == dfn[u]) {
        id ++; T[id].clear();
        while(1) {
          int x = st[top --];
          T[x].pb(id); T[id].pb(x);
          if(x == v) break ;
        }
        T[u].pb(id); T[id].pb(u);
      }
    } else low[u] = min(low[u], dfn[v]);
  }
}
void dfs(int u, int fa = 0) {
  dfn[u] = ++ idx; f[u] = fa;
  for(int v : T[u]) if(v != fa) dfs(v, u);
  dr[u] = idx;
}
bool intree(int u, int v) {
  return dfn[u] <= dfn[v] && dfn[v] <= dr[u];
}
int main() {
  int test;
  scanf("%d", &test);
  while(test --) {
    scanf("%d%d%s", &n, &m, s + 1);
    id = n; top = 0;
    rep(i, 1, n) {
      T[i].clear(); G[i].clear();
    }
    vector< pair<int, int> > edge;
    rep(i, 1, m) {
      int u, v;
      scanf("%d%d", &u, &v);
      u ++; v ++;
      if(s[u] == s[v]) edge.pb({u, v});
      else { G[u].pb(v); G[v].pb(u); }
    }
    fill(dfn + 1, dfn + n + 1, 0); idx = 0; tarjan(1); idx = 0; dfs(1);
    bool yes = 0;
    for(auto x : edge) {
      int u = x.first, v = x.second;
      if(!dfn[u] || !dfn[v]) continue ;
      if(intree(f[u], v) || intree(f[v], u) || u == 1 || v == 1) {
        yes = 1; break ;
      }
    }
    puts(yes ? "yes" : "no");
  }
  return 0;
}