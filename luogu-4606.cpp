#include <algorithm>
#include <cstdio>
#include <vector>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; i ++)
#define per(i, j, k) for(int i = j; i >= k; i --)
using namespace std;
const int N = 2e5 + 10;
int n, m, q, id, idx, dfn[N], low[N], st[N], top;
vector<int> G[N], T[N];
void tarjan(int u) {
   dfn[u] = low[u] = ++ idx; st[++ top] = u;
   rep(i, 0, (int) G[u].size() - 1) {
      int v = G[u][i];
      if(!dfn[v]) {
         tarjan(v); low[u] = min(low[u], low[v]);
         if(low[v] == dfn[u]) {
            T[++ id].clear();
            for(; st[top] != v; top --) {
               T[id].pb(st[top]); T[st[top]].pb(id);
            }
            T[id].pb(v); T[v].pb(id); top --;
            T[id].pb(u); T[u].pb(id);
         }
      } else {
         low[u] = min(low[u], dfn[v]);
      }
   }
}
int f[N][18], d[N], dis[N], num[N];
void dfs(int u, int fa = 0) {
   f[u][0] = fa; d[u] = d[fa] + 1; num[u] = ++ idx;
   rep(i, 1, 17) f[u][i] = f[f[u][i - 1]][i - 1];
   rep(i, 0, (int) T[u].size() - 1) {
      int v = T[u][i];
      if(v != fa) {
         dis[v] = dis[u] + (v <= n);
         dfs(v, u);
      }
   }
}
int lca(int u, int v) {
   if(d[u] < d[v]) swap(u, v);
   int c = d[u] - d[v];
   per(i, 17, 0) if(c >> i & 1) u = f[u][i];
   if(u == v) return u;
   per(i, 17, 0) if(f[u][i] ^ f[v][i]) {
      u = f[u][i]; v = f[v][i];
   }
   return f[u][0];
}
int dist(int u, int v) {
   return dis[u] + dis[v] - 2 * dis[lca(u, v)];
}
bool cmp(int x, int y) { return num[x] < num[y]; }
int main() {
   int test; scanf("%d", &test);
   while(test --) {
      scanf("%d%d", &n, &m);
      rep(i, 1, n) {
         G[i].clear(); T[i].clear(); dfn[i] = 0;
      }
      idx = top = 0; id = n;
      rep(i, 1, m) {
         int u, v;
         scanf("%d%d", &u, &v);
         G[u].pb(v); G[v].pb(u);
      }
      tarjan(1); idx = dis[1] = 0; dfs(1);
      scanf("%d", &q);
      static int s, seq[N];
      rep(i, 1, q) {
         scanf("%d", &s);
         rep(j, 1, s) scanf("%d", seq + j);
         sort(seq + 1, seq + s + 1, cmp);
         int ans = 0;
         rep(j, 1, s) {
            ans += dist(seq[j], seq[j == s ? 1 : j + 1]);
         }
         ans = ans / 2 + (lca(seq[1], seq[s]) <= n);
         printf("%d\n", ans - s);
      }
   }
   return 0;
}