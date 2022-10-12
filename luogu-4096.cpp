#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long double db;
typedef long long ll;
const ll INF = 123456789123456789ll;
const int N = 1e5 + 5;
struct Edge { int v, w, nxt; } e[N * 2];
int n, q, ec, hd[N], d[N], sz[N], son[N], fa[N];
int dfn[N], top[N];
ll dep[N], sum[N];
void add(int u, int v, int w) {
   e[ec] = {v, w, hd[u]}; hd[u] = ec ++;
}
void dfs(int u, int p = 0) {
   sz[u] = 1; d[u] = d[fa[u] = p] + 1;
   for(int i = hd[u]; ~ i; i = e[i].nxt) if(e[i].v ^ p) {
      dep[e[i].v] = dep[u] + e[i].w;
      dfs(e[i].v, u); sz[u] += sz[e[i].v];
      if(sz[e[i].v] > sz[son[u]]) son[u] = e[i].v;
   }
}
void dfs2(int u, int t) {
   top[u] = t; dfn[u] = ++ *dfn; sum[*dfn] = dep[u];
   if(!son[u]) return ;
   dfs2(son[u], t);
   for(int i = hd[u]; ~ i; i = e[i].nxt) {
      if(e[i].v != fa[u] && e[i].v != son[u]) {
         dfs2(e[i].v, e[i].v);
      }
   }
}
struct seg {
   int id;
   ll k, b;
   ll val(ll x) { return k * x + b; }
} a[N * 4];
ll low[N * 4];
void pushup(int u, int l, int r) {
   if(l == r) low[u] = a[u].id ? a[u].val(sum[l]) : INF;
   else {
      low[u] = min(low[u << 1], low[u << 1 | 1]);
      if(a[u].id) {
         low[u] = min(low[u], min(a[u].val(sum[l]), a[u].val(sum[r])));
      }
   }
}
void build(int u, int l, int r) {
   low[u] = INF;
   if(l == r) return ;
   int mid = (l + r) >> 1;
   build(u << 1, l, mid);
   build(u << 1 | 1, mid + 1, r);
}
void modify(int u, int l, int r, seg x) {
   if(!a[u].id) { a[u] = x; pushup(u, l, r); return ; }
   ll l1 = a[u].val(sum[l]), r1 = a[u].val(sum[r]), l2 = x.val(sum[l]), r2 = x.val(sum[r]);
   if(l1 <= l2 && r1 <= r2) return ;
   if(l2 <= l1 && r2 <= r1) { a[u] = x; pushup(u, l, r); return ; }
   int mid = (l + r) >> 1;
   db cs = (x.b - a[u].b) / (a[u].k - x.k);
   if(cs <= sum[mid]) {
      if(l2 <= l1) modify(u << 1, l, mid, x);
      else modify(u << 1, l, mid, a[u]), a[u] = x;
   } else {
      if(r2 <= r1) modify(u << 1 | 1, mid + 1, r, x);
      else modify(u << 1 | 1, mid + 1, r, a[u]), a[u] = x;
   }
   pushup(u, l, r);
}
void modify(int u, int l, int r, int ql, int qr, seg x) {
   if(l == ql && r == qr) { modify(u, l, r, x); return ; }
   int mid = (l + r) >> 1;
   if(qr <= mid) modify(u << 1, l, mid, ql, qr, x);
   else if(ql > mid) modify(u << 1 | 1, mid + 1, r, ql, qr, x);
   else {
      modify(u << 1, l, mid, ql, mid, x);
      modify(u << 1 | 1, mid + 1, r, mid + 1, qr, x);
   }
   pushup(u, l, r);
}
int LCA(int x, int y) {
   while(top[x] != top[y]) {
      if(d[top[x]] < d[top[y]]) swap(x, y);
      x = fa[top[x]];
   }
   return d[x] < d[y] ? x : y;
}
void pushseg(int u, int v, ll a, ll b) {
   int x = u, y = v, lca = LCA(u, v);
   bool isx = 1; seg se;
   while(top[x] != top[y]) {
      if(d[top[x]] < d[top[y]]) swap(x, y), isx ^= 1;
      if(isx) {
         se = {1, -a, dep[u] * a + b};
      } else {
         se = {1, a, (dep[u] - 2 * dep[lca]) * a + b};
      }
      modify(1, 1, n, dfn[top[x]], dfn[x], se);
      x = fa[top[x]];
   }
   if(dfn[x] > dfn[y]) swap(x, y), isx ^= 1;
   if(isx) {
      se = {1, a, ((dep[u] - dep[x]) * a + b) - a * sum[dfn[x]]};
   } else {
      se = {1, -a, ((dep[u] - dep[y]) * a + b) + a * sum[dfn[y]]};
   }
   modify(1, 1, n, dfn[x], dfn[y], se);
}
ll query(int u, int l, int r, int ql, int qr) {
   if(l == ql && r == qr) return low[u];
   int mid = (l + r) >> 1; ll ans = a[u].id ? (ll) min(a[u].val(sum[ql]), a[u].val(sum[qr])) : INF;
   if(qr <= mid) ans = min(ans, query(u << 1, l, mid, ql, qr));
   else if(ql > mid) ans = min(ans, query(u << 1 | 1, mid + 1, r, ql, qr));
   else {
      ans = min(ans, min(query(u << 1, l, mid, ql, mid), query(u << 1 | 1, mid + 1, r, mid + 1, qr)));
   }
   return ans;
}
ll query(int u, int v) {
   ll ans = INF;
   for(; top[u] ^ top[v]; u = fa[top[u]]) {
      if(d[top[u]] < d[top[v]]) swap(u, v);
      ans = min(ans, query(1, 1, n, dfn[top[u]], dfn[u]));
   }
   if(dfn[u] > dfn[v]) swap(u, v);
   ans = min(ans, query(1, 1, n, dfn[u], dfn[v]));
   return ans;
}
int main() {
   scanf("%d%d", &n, &q);
   fill(hd + 1, hd + n + 1, -1); ec = 0;
   int u, v, w, op, a, b;
   rep(i, 1, n - 1) {
      scanf("%d%d%d", &u, &v, &w);
      add(u, v, w); add(v, u, w);
   }
   dfs(1); dfs2(1, 1); build(1, 1, n);
   rep(i, 1, q) {
      scanf("%d%d%d", &op, &u, &v);
      if(op == 1) {
         scanf("%d%d", &a, &b);
         pushseg(u, v, a, b);
      } else {
         printf("%lld\n", query(u, v));
      }
   }
   return 0;
}