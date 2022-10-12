#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
#define pb push_back

typedef long long ll;

const int N = 2e5 + 10;
const int INF = 2e9 + 10;

int n, m, sz, logn, d[N], f[N][20];
vector<int> G[N];
void dfs(int u, int fa = 0) {
   f[u][0] = fa; d[u] = d[fa] + 1;
   rep(i, 1, logn - 1) {
      f[u][i] = f[f[u][i - 1]][i - 1];
      if(!f[u][i]) break ;
   }
   for(int v : G[u]) if(v ^ fa) dfs(v, u);
}
int lca(int u, int v) {
   if(d[u] < d[v]) swap(u, v);
   int c = d[u] - d[v];
   per(i, logn - 1, 0) if(c >> i & 1) u = f[u][i];
   if(u == v) return v;
   per(i, logn - 1, 0) if(f[u][i] ^ f[v][i])
      u = f[u][i], v = f[v][i];
   return f[v][0];
}
int dis(int u, int v) {
   return d[u] + d[v] - (d[lca(u, v)] << 1);
}
struct node {
   int t, u;
} a[N];
int top, up[N], ti[N], pos[N];
bool mark, iq[N];
queue<int> q;
void build() {
   if(mark) {
      fill(up + 1, up + n + 1, INF); mark = 0;
   }
   if(!top) return ;
   rep(i, 1, top) pos[a[i].t] = i, iq[i] = 0;
   fill(ti + 1, ti + n + 1, INF);
   int st = 1;
   rep(i, 1, top) if(a[st].t > a[i].t) st = i;
   rep(i, 1, top) if(a[st].t == a[i].t) {
      iq[i] = 1; q.push(a[i].u); ti[a[i].u] = a[i].t;
   }
   while(q.size()) {
      int u = q.front(); q.pop();
      for(int v : G[u]) if(ti[v] == INF) {
         q.push(v); ti[v] = ti[u] + 1;
         int p = pos[ti[v]];
         if(p && !iq[p]) {
            q.push(a[p].u); iq[p] = 1;
            ti[a[p].u] = ti[v];
         }
      }
   }
   rep(i, 1, top) pos[a[i].t] = 0;
   rep(i, 1, n) up[i] = min(up[i], ti[i]);
   // rep(i, 1, n) printf("up %d = %d\n", i, up[i]);
}
bool query(int t, int u) {
   if(!mark && t >= up[u]) {
      return 1;
   }
   rep(i, 1, top) {
      if(t - a[i].t >= dis(a[i].u, u)) {
         return 1;
      }
   }
   return 0;
}
int main() {
   scanf("%d%d", &n, &m);
   for(logn = 1; (1 << logn) <= n; logn ++) ;
   int u, v;
   rep(i, 1, n - 1) {
      scanf("%d%d", &u, &v);
      G[u].pb(v); G[v].pb(u);
   }
   dfs(1);
   int op, x; //O(q(n / s + s))
   sz = max(1, (int)sqrt(n));
   fill(up + 1, up + n + 1, INF);
   rep(i, 1, m) {
      if(i % sz == 0) build(), top = 0;
      scanf("%d%d", &op, &x);
      if(op == 1) {
         a[++ top] = {i, x};
      }
      if(op == 2) {
         mark = 1; top = 0;
      }
      if(op == 3) {
         puts(query(i, x) ? "wrxcsd" : "orzFsYo");
      }
   }
   return 0;
}