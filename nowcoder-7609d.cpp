#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
#define pb push_back
typedef long long ll;

const int N = 1e5 + 20;

struct node {
   ll w, b, c; int u;
   bool operator < (const node &rhs) const {
      return b * rhs.c < c * rhs.b;
   }
} a[N];
int n, p[N], f[N];
vector<int> G[N];
ll ATK, DEF, HP;
bool use[N];
void dfs(int u, int fa = 0) {
   p[u] = fa;
   for(int v : G[u]) if(v ^ fa) dfs(v, u);
}
int find(int u) {
   return u == f[u] ? u : f[u] = find(f[u]);
}
priority_queue<node> q;
int main() {
   scanf("%d", &n);
   rep(i, 1, n) f[i] = i;
   int u, v;
   rep(i, 1, n - 1) {
      scanf("%d%d", &u, &v);
      G[u].pb(v); G[v].pb(u);
   }
   dfs(1);
   scanf("%lld%lld%lld", &HP, &ATK, &DEF);
   rep(i, 2, n) {
      ll atk, def, hp, b;
      scanf("%lld%lld%lld%lld", &hp, &atk, &def, &b);
      ll c = (hp % (ATK - def) == 0 ? -1 : 0) + (hp / (ATK - def));
      q.push(a[i] = {atk * c, b, c, i});
   }
   while(q.size()) {
      node x = q.top(); q.pop();
      if(x.b != a[x.u].b) continue ;
      // printf("%lld\n", (ll)x.u);
      int rt = find(p[x.u]);
      f[x.u] = rt;
      a[rt].w += a[x.u].w - a[rt].b * a[x.u].c;
      a[rt].b += a[x.u].b;
      a[rt].c += a[x.u].c;
      if(rt ^ 1) q.push(a[rt]);
   }
   if(0&&HP - a[1].w <= 0) puts("-1");
   else printf("%lld\n", HP - a[1].w);
   return 0;
}