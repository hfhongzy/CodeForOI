#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e6 + 20;
int n, q, st[N], top, dfn[N], seq[N], s, logn, f[N][21], d[N];
vector<int> G[N], T[N];
void dfs(int u, int p = 0) {
   dfn[u] = ++ *dfn; f[u][0] = p; d[u] = d[p] + 1;
   rep(i, 1, logn) {
      f[u][i] = f[f[u][i - 1]][i - 1];
      if(!f[u][i]) break ;
   }
   for(int v : G[u]) if(v ^ p) dfs(v, u);
}
int LCA(int u, int v) {
   if(d[u] < d[v]) swap(u, v);
   int c = d[u] - d[v];
   per(i, logn, 0) if(c >> i & 1) u = f[u][i];
   if(u == v) return v;
   per(i, logn, 0) if(f[u][i] ^ f[v][i]) u = f[u][i], v = f[v][i];
   return f[u][0];
}
int sz[N], Max[N], Min[N], ans1, ans2;
bool mark[N];
ll sum;
void dfs2(int u, int p = 0) {
   sz[u] = mark[u]; Max[u] = -N; Min[u] = N;
   if(mark[u]) Min[u] = Max[u] = 0;
   for(int v : T[u]) if(v ^ p) {
      dfs2(v, u); int w = d[v] - d[u];
      sz[u] += sz[v];
      sum += (ll) w * (s - sz[v]) * sz[v];
      Max[v] += w; Min[v] += w;
      ans1 = max(ans1, Max[v] + Max[u]);
      ans2 = min(ans2, Min[v] + Min[u]);
      Max[u] = max(Max[u], Max[v]);
      Min[u] = min(Min[u], Min[v]);
   }
}
void clr(int u, int p = 0) {
   for(int v : T[u]) if(v ^ p) clr(v, u);
   T[u].clear(); mark[u] = 0;
}
void insert(int u) {
   if(top) {
      int x = LCA(st[top], u);
      if(x != st[top]) {
         while(dfn[st[top - 1]] > dfn[x]) {
            T[st[top - 1]].pb(st[top]);
            top --;
         }
         T[x].pb(st[top --]);
         if(x != st[top]) st[++ top] = x;
      }
   }
   st[++ top] = u;
}
int main() {
   scanf("%d", &n);
   for(logn = 1; (1 << logn) <= n; logn ++) ;
   logn --;
   int u, v;
   rep(i, 1, n - 1) {
      scanf("%d%d", &u, &v);
      G[u].pb(v); G[v].pb(u);
   }
   dfs(1);
   scanf("%d", &q);
   rep(Q, 1, q) {
      scanf("%d", &s);
      rep(i, 1, s) scanf("%d", seq + i), mark[seq[i]] = 1;
      sort(seq + 1, seq + s + 1, [&](int x, int y) { return dfn[x] < dfn[y]; });
      top = 0;
      if(seq[1] != 1) insert(1);
      rep(i, 1, s) insert(seq[i]);
      rep(i, 1, top - 1) T[st[i]].pb(st[i + 1]);
      sum = ans1 = 0; ans2 = N;
      dfs2(1);
      printf("%lld %d %d\n", sum, ans2, ans1);
      clr(1);
   }
   return 0;
}