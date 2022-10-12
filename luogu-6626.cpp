#include <bits/stdc++.h>
#define pb push_back
#define LOG(...) fprintf(stderr, __VA_ARGS__);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 2e5 + 10;
int n, m, rt, siz, sz[N], f[N], ans[N];
vector<int> G[N];
struct node { int d, id; };
vector<node> Q[N];
bool vis[N];
void findrt(int u, int fa = 0) {
  f[u] = 0; sz[u] = 1;
  for(int v : G[u]) if(v != fa && !vis[v]) {
    findrt(v, u);
    sz[u] += sz[v];
    f[u] = max(f[u], sz[v]);
  }
  f[u] = max(f[u], siz - sz[u]);
  if(!rt || f[rt] > f[u]) rt = u;
}
int maxd, d[N], seq[N], s;
void dfs(int u, int l, int fa = 0) {
  d[u] = l; maxd = max(maxd, l); seq[++ s] = u;
  for(int v : G[u]) if(!vis[v] && v != fa) {
    dfs(v, l + 1, u);
  }
}
int cnt[N];
void calc(int u, int coef, int base) {
  maxd = s = 0; dfs(u, base);
  rep(i, 1, s) cnt[d[seq[i]]] ++;
  rep(i, 1, s) for(node u : Q[seq[i]])
    if(u.d - d[seq[i]] >= 0) {
      ans[u.id] += coef * cnt[u.d - d[seq[i]]];
    }
  fill(cnt, cnt + maxd + 1, 0);
}
void solve(int u) {
  vis[u] = 1;
  calc(u, 1, 0);
  for(int v : G[u]) if(!vis[v]) {
    calc(v, -1, 1);
  }
  for(int v : G[u]) if(!vis[v]) {
    rt = 0; siz = sz[v]; findrt(v); solve(rt);
  }
}
int main() {
  int test;
  scanf("%d", &test);
  while(test --) {
    scanf("%d%d", &n, &m);
    rep(i, 1, n) Q[i].clear(), G[i].clear(), vis[i] = 0;
    rep(i, 1, n - 1) {
      int x, y;
      scanf("%d%d", &x, &y);
      G[x].pb(y); G[y].pb(x);
    }
    rep(i, 1, m) {
      ans[i] = 0;
      int x, d;
      scanf("%d%d", &x, &d);
      Q[x].pb({d, i});
    }
    siz = n; rt = 0; findrt(1); solve(rt);
    rep(i, 1, m) printf("%d\n", ans[i]);
  }
  return 0;
}