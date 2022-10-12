#include <algorithm>
#include <cstdio>
#include <vector>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; i ++)
using namespace std;
typedef long long ll;
const int N = 1 << 20 | 5;
int n, fa[N], son[N], sz[N], d[N];
int top[N], dfn[N], pos[N], idx;
vector<int> G[N];
void dfs1(int u) {
   sz[u] = 1; son[u] = 0; d[u] = d[fa[u]] + 1;
   rep(i, 0, (int) G[u].size() - 1) {
      int v = G[u][i];
      dfs1(v); sz[u] += sz[v];
      if(sz[v] > sz[son[u]]) son[u] = v;
   }
}
void dfs2(int u, int t) {
   top[u] = t; dfn[u] = ++ idx; pos[idx] = u;
   if(!son[u]) return ;
   dfs2(son[u], t);
   rep(i, 0, (int) G[u].size() - 1) {
      int v = G[u][i];
      if(!dfn[v]) dfs2(v, v);
   }
}
ll w1[N << 2], w2[N << 2], s1[N << 2], s2[N << 2], tag[N << 2];
void build(int u, int l, int r) {
   if(l == r) {
      int Tn = pos[l];
      w1[u] = (ll) d[Tn] * d[Tn];
      w2[u] = Tn == 1 ? 0 : (d[Tn] - 1ll) * (d[Tn] - 1ll);
      return ;
   }
   int mid = (l + r) >> 1;
   build(u << 1, l, mid);
   build(u << 1 | 1, mid + 1, r);
   w1[u] = w1[u << 1] + w1[u << 1 | 1];
   w2[u] = w2[u << 1] + w2[u << 1 | 1];
}
void addtag(int u, ll val) {
   s1[u] += val * w1[u];
   s2[u] += val * w2[u];
   tag[u] += val;
}
void pdown(int u) {
   if(tag[u]) {
      addtag(u << 1, tag[u]);
      addtag(u << 1 | 1, tag[u]);
      tag[u] = 0;
   }
}
void modify(int u, int l, int r, int ql, int qr, int val) {
   if(l == ql && r == qr) {
      addtag(u, val);
      return ;
   }
   int mid = (l + r) >> 1; pdown(u);
   if(qr <= mid) modify(u << 1, l, mid, ql, qr, val);
   else if(ql > mid) modify(u << 1 | 1, mid + 1, r, ql, qr, val);
   else {
      modify(u << 1, l, mid, ql, mid, val);
      modify(u << 1 | 1, mid + 1, r, mid + 1, qr, val);
   }
   s1[u] = s1[u << 1] + s1[u << 1 | 1];
   s2[u] = s2[u << 1] + s2[u << 1 | 1];
}
ll query(int u, int l, int r, int ql, int qr) {
   if(l == ql && r == qr) {
      return s1[u] - s2[u];
   }
   int mid = (l + r) >> 1; pdown(u);
   if(qr <= mid) return query(u << 1, l, mid, ql, qr);
   if(ql > mid) return query(u << 1 | 1, mid + 1, r, ql, qr);
   return query(u << 1, l, mid, ql, mid) + query(u << 1 | 1, mid + 1, r, mid + 1, qr);
}
void modify(int u, int v, int val) {
   while(top[u] != top[v]) {
      if(d[top[u]] < d[top[v]]) swap(u, v);
      modify(1, 1, n, dfn[top[u]], dfn[u], val);
      u = fa[top[u]];
   }
   if(dfn[u] > dfn[v]) swap(u, v);
   modify(1, 1, n, dfn[u], dfn[v], val);
}
ll query(int u, int v) {
   ll ans = 0;
   while(top[u] != top[v]) {
      if(d[top[u]] < d[top[v]]) swap(u, v);
      ans += query(1, 1, n, dfn[top[u]], dfn[u]);
      u = fa[top[u]];
   }
   if(dfn[u] > dfn[v]) swap(u, v);
   ans += query(1, 1, n, dfn[u], dfn[v]);
   return ans;
}
int main() {
   scanf("%d", &n);
   rep(i, 2, n) {
      scanf("%d", fa + i);
      G[fa[i]].pb(i);
   }
   dfs1(1); dfs2(1, 1); build(1, 1, n);
   rep(i, 1, n) {
      modify(1, i, 1);
      int x; scanf("%d", &x);
      printf("%lld\n", query(1, x));
   }
   return 0;
}
/*
(add) [x, root] : sz_app[u] * d[u]^2 w1[u]
(dec) [x, root) : sz_app[u] * (d[u]-1)^2 w2[u]
*/