#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 1e5 + 10;
int n, q, size, w[N], num[N], ans[N];
int d[N], sz[N], son[N], fa[N], top[N], pos[N * 2], dl[N], dr[N];
vector<int> G[N]; 
struct node {
   int l, r, lca, id, ll;
   bool operator < (node b) const {
      return ll < b.ll || (ll == b.ll && r < b.r);
   }
} a[N];
void dfs(int u, int p = 0) {
   sz[u] = 1; fa[u] = p; d[u] = d[p] + 1;
   for(int v : G[u]) if(v ^ p) {
      dfs(v, u); sz[u] += sz[v];
      if(sz[v] > sz[son[u]]) son[u] = v;
   }
}
void dfs2(int u, int t) {
   top[u] = t; pos[++ *pos] = u; dl[u] = *pos;
   if(son[u]) {
      dfs2(son[u], t);
      for(int v : G[u]) {
         if(v != fa[u] && v != son[u]) {
            dfs2(v, v);
         }
      }
   }
   pos[++ *pos] = u; dr[u] = *pos;
}
int LCA(int u, int v) {
   for(; top[u] ^ top[v]; u = fa[top[u]])
      if(d[top[u]] < d[top[v]]) swap(u, v);
   return d[u] > d[v] ? v : u;
}
int cnt[N], cur;
bool use[N];
void mdf(int u) {
   if(!use[u]) {
      use[u] = 1;
      if(!cnt[w[u]] ++) {
         cur ++;
      }
   } else {
      use[u] = 0;
      if(! -- cnt[w[u]]) {
         cur --;
      }
   }
}
int main() {
   scanf("%d%d", &n, &q);
   rep(i, 1, n) scanf("%d", w + i), num[i] = w[i];
   sort(num + 1, num + n + 1);
   rep(i, 1, n) w[i] = lower_bound(num + 1, num + n + 1, w[i]) - num;
   int u, v;
   rep(i, 1, n - 1) {
      scanf("%d%d", &u, &v);
      G[u].pb(v); G[v].pb(u);
   }
   dfs(1); dfs2(1, 1);
   rep(i, 1, q) {
      scanf("%d%d", &u, &v);
      if(dl[u] > dl[v]) swap(u, v);
      a[i].id = i;
      a[i].lca = LCA(u, v);
      if(a[i].lca == u) {
         a[i].l = dl[u]; a[i].r = dl[v];
         a[i].lca = 0;
      } else {
         a[i].l = dr[u]; a[i].r = dl[v];
      }
   }
   size = n / sqrt(q);
   if(size < 1) size = 1;
   rep(i, 1, q) a[i].ll = a[i].l / size;
   sort(a + 1, a + q + 1);
   int l = 1, r = 0;
   rep(i, 1, q) {
      while(l > a[i].l) mdf(pos[-- l]);
      while(r < a[i].r) mdf(pos[++ r]);
      while(l < a[i].l) mdf(pos[l ++]);
      while(r > a[i].r) mdf(pos[r --]);
      if(a[i].lca) mdf(a[i].lca);
      ans[a[i].id] = cur;
      if(a[i].lca) mdf(a[i].lca);
   }
   rep(i, 1, q) printf("%d\n", ans[i]);
   return 0;
}