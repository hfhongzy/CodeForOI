#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 1e5 + 10;
int n, m, logn, idx, dfn[N], dr[N], col[N], d[N], f[N][18];
vector<int> G[N];

template<class T>
struct SMT {
   T w[N * 4], tag[N * 4];
   void addtag(int u, T v) {
      tag[u] += v; w[u] += v;
   }
   void up(int u) {
      w[u] = max(w[u << 1], w[u << 1 | 1]);
   }
   void down(int u) {
      if(tag[u]) {
         addtag(u << 1, tag[u]);
         addtag(u << 1 | 1, tag[u]);
         tag[u] = 0;
      }
   }
   void build(int u, int l, int r, T *seq) {
      if(l == r) { w[u] = seq[l]; return ; }
      int mid = (l + r) >> 1;
      build(u << 1, l, mid, seq);
      build(u << 1 | 1, mid + 1, r, seq);
      up(u);
   }
   void modify(int u, int l, int r, int ql, int qr, T v) {
      if(l == ql && r == qr) { addtag(u, v); return ; }
      int mid = (l + r) >> 1; down(u);
      if(qr <= mid) modify(u << 1, l, mid, ql, qr, v);
      else if(ql > mid) modify(u << 1 | 1, mid + 1, r, ql, qr, v);
      else {
         modify(u << 1, l, mid, ql, mid, v);
         modify(u << 1 | 1, mid + 1, r, mid + 1, qr, v);
      }
      up(u);
   }
   T query(int u, int l, int r, int ql, int qr) {
      if(l == ql && r == qr) return w[u];
      int mid = (l + r) >> 1; down(u);
      if(qr <= mid) return query(u << 1, l, mid, ql, qr);
      if(ql > mid) return query(u << 1 | 1, mid + 1, r, ql, qr);
      return max(query(u << 1, l, mid, ql, mid), query(u << 1 | 1, mid + 1, r, mid + 1, qr));
   }
};
SMT<int> seg;
struct LinkCutTree {

   int fa[N], ch[N][2];
   int dir(int u) { return ch[fa[u]][1] == u ? 1 : (ch[fa[u]][0] == u ? 0 : -1); }
   void rotate(int u) {
      int d = dir(u), f = fa[u];
      if(fa[u] = fa[f], ~ dir(f)) ch[fa[u]][dir(f)] = u;
      if(ch[f][d] = ch[u][d ^ 1]) fa[ch[f][d]] = f;
      fa[ch[u][d ^ 1] = f] = u;
   }
   void splay(int u) {
      for(; ~ dir(u); rotate(u)) if(~ dir(fa[u]))
         rotate(dir(u) == dir(fa[u]) ? fa[u] : u);
   }
   int find(int u) {
      while(ch[u][0]) u = ch[u][0];
      return u;
   }
   void access(int u) {
      for(int v = 0; u; v = u, u = fa[u]) {
         splay(u);
         int t = find(ch[u][1]);
         if(t) seg.modify(1, 1, n, dfn[t], dr[t], 1);
         ch[u][1] = v;
         if(t = find(v)) seg.modify(1, 1, n, dfn[t], dr[t], -1);
      }
   }
} lct;
void dfs(int u, int fa = 0) {
   d[u] = d[fa] + 1; f[u][0] = fa;
   rep(i, 1, logn - 1) {
      f[u][i] = f[f[u][i - 1]][i - 1];
      if(!f[u][i]) break ;
   }
   dfn[u] = ++ idx; lct.fa[u] = fa; col[idx] = d[u];
   for(int v : G[u]) if(v ^ fa) dfs(v, u);
   dr[u] = idx;
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
int qry(int u) {
   return seg.query(1, 1, n, dfn[u], dfn[u]);
}
int main() {
   scanf("%d%d", &n, &m);
   for(logn = 1; (1 << logn) <= n; logn ++) ;
   int op, u, v;
   rep(i, 1, n - 1) {
      scanf("%d%d", &u, &v);
      G[u].pb(v); G[v].pb(u);
   }
   dfs(1); seg.build(1, 1, n, col);
   rep(i, 1, m) {
      scanf("%d%d", &op, &u);
      if(op == 1) {
         lct.access(u);
      }
      if(op == 2) {
         scanf("%d", &v);
         printf("%d\n", qry(u) + qry(v) - 2 * qry(lca(u, v)) + 1);
      }
      if(op == 3) {
         printf("%d\n", seg.query(1, 1, n, dfn[u], dr[u]));
      }
   }
   return 0;
}