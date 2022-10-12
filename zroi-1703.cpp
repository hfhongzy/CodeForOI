#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
int n, k, h, a[N], d1[N];
vector<int> G[N];
ll res[N];
void dfs0(int u, int fa = 0) {
   d1[u] = fa ? d1[fa] + 1 : 0;
   for(int v : G[u]) if(v ^ fa) dfs0(v, u);
}
int rt, siz, sz[N], f[N];
bool mark[N];
void findrt(int u, int fa = 0) {
   sz[u] = f[u] = 1;
   for(int v : G[u]) if(v != fa && !mark[v]) {
      findrt(v, u); sz[u] += sz[v]; f[u] = max(f[u], sz[v]);
   }
   f[u] = max(f[u], siz - sz[u]);
   if(!rt || f[rt] > f[u]) rt = u;
}
int maxd;
ll sum[N], tmp[N], suf[N];
void dfs(int u, int dep, int fa = 0) {
   maxd = max(maxd, dep);
   if(dep && dep <= h) { suf[dep] += a[u]; sum[dep % k] += a[u]; tmp[0] += a[u] * ((h - dep) / k + 1ll); }
   if(dep == h) return ;
   for(int v : G[u]) if(v != fa && !mark[v]) dfs(v, dep + 1, u);
}
void dfs2(int u, int dep, int w, int fa = 0) {
   if(dep) res[u] += tmp[dep] * w;
   if(dep == h) return ;
   for(int v : G[u]) if(v != fa && !mark[v]) dfs2(v, dep + 1, w, u);
}
void dfs3(int u, int dep, int fa = 0) {
   if(dep) {
      res[rt] += h < dep ? 0 : ((h - dep) / k + 1ll) * a[u];
      res[u] += h < dep ? 0 : ((h - dep) / k + 1ll) * a[rt];
   }
   for(int v : G[u]) if(v != fa && !mark[v]) dfs3(v, dep + 1, u);
}
void calc(int u, int bas, int w) {
   tmp[0] = maxd = 0; dfs(u, bas);
   per(i, maxd - 1, 0) suf[i] += (i + k <= maxd ? suf[i + k] : 0);
   rep(i, 0, maxd - 1) {
      int x = (h - i) % k;
      if(x > maxd) tmp[i + 1] = tmp[i];
      else {
         tmp[i + 1] = tmp[i] - sum[x];
         int q = (h - i - x + k) / k;
         tmp[i + 1] += (q * k + x > maxd ? 0 : suf[q * k + x]);
      }
   }
   dfs2(u, bas, w);
   rep(i, 0, maxd) sum[i] = suf[i] = 0;
}
void solve(int u) {
   mark[u] = 1; dfs3(u, 0); calc(u, 0, 1);
   for(int v : G[u]) if(!mark[v]) calc(v, 1, -1);
   for(int v : G[u]) if(!mark[v]) {
      siz = sz[v]; rt = 0; findrt(v); solve(rt);
   }
}
int main() {
   scanf("%d%d%d", &n, &k, &h);
   rep(i, 1, n) scanf("%d", a + i);
   int u, v;
   rep(i, 1, n - 1) { scanf("%d%d", &u, &v); G[u].pb(v); G[v].pb(u); }
   dfs0(1);
   siz = n; rt = 0; findrt(1); solve(rt);
   ll ans = 1ll << 62;
   rep(i, 1, n) if(d1[i] <= h) ans = min(ans, res[i] + (h + k - 1ll) / k * a[i]);
   printf("%lld\n", ans);
   return 0;
}