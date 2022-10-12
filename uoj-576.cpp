#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
char gc() {
   // return getchar();
   static char buf[1 << 17], *S, *T;
   if(S == T) T = (S = buf) + fread(buf, 1, 1 << 17, stdin);
   return S == T ? EOF : *S ++;
}
template<class T> void read(T &x) {
   x = 0; char c = gc(); bool na = 0;
   for(; c < '0' || c > '9'; c = gc()) na |= c == '-';
   for(; c >= '0' && c <= '9'; c = gc()) x = x * 10 + (c & 15);
   if(na) x = -x;
}
const int N = 2e5 + 10;
int n, m, q, d[N], top[N], dis[N], ID[N], sz[N], c[N], fa[N], len[N], siz[N], cur[N], op[N], qu[N], qv[N], pos[N];
int dl[N], dr[N], idx, son[N], f[N][18];
vector<int> G[N];
ll val[N];
namespace LCA {

int f[20][N * 2], pos[N], id, lg[N * 2];
int mi(int u, int v) { return d[u] < d[v] ? u : v; }
void dfs(int u) {
   pos[u] = ++ id; f[0][id] = u;
   for(int v : G[u]) dfs(v), f[0][++ id] = u;
}
void build() {
   dfs(1);
   lg[1] = 0;
   rep(i, 2, id) lg[i] = lg[i >> 1] + 1;
   for(int j = 1; (1 << j) <= id; j ++)
      for(int i = 1; i + (1 << j) - 1 <= id; i ++)
         f[j][i] = mi(f[j - 1][i], f[j - 1][i + (1 << (j - 1))]);
}
int get(int u, int v) {
   u = pos[u]; v = pos[v];
   if(u > v) swap(u, v);
   int k = lg[v - u + 1];
   return mi(f[k][u], f[k][v - (1 << k) + 1]);
}

}
void dfs(int u) {
   f[u][0] = fa[u]; sz[u] = 1;
   rep(j, 1, 16) if(!(f[u][j] = f[f[u][j - 1]][j - 1])) break ;
   for(int v : G[u]) {
      d[v] = d[u] + 1, dis[v] = dis[u] + len[v], dfs(v), sz[u] += sz[v];
      if(sz[v] >= sz[son[u]]) son[u] = v;
   }
}
void dfs2(int u, int t) {
   top[u] = t; dl[u] = ++ idx; ID[idx] = u;
   if(son[u]) {
      dfs2(son[u], t);
      for(int v : G[u]) if(!top[v]) dfs2(v, v);
   }
   dr[u] = idx;
}
int dist(int u, int v) { return dis[u] + dis[v] - 2 * dis[LCA::get(u, v)]; }
int dist2(int u, int ff) { return dis[u] - dis[ff]; }

struct diam {
   int u, v, d;
   bool operator == (diam b) const { return (u == b.u && v == b.v) || (u == b.v && v == b.u); }
   void insert(int x) {
      if(!x) return ;
      if(!u) { u = v = x; d = 0; return ; }
      if(u == v) { v = x; d = dist(u, v); return ; }
      int d1 = dist(x, u), d2 = dist(x, v);
      if(d1 < d2) { swap(u, v); swap(d1, d2); }
      if(d1 <= d) return ;
      v = x; d = d1;
   }
   diam operator + (diam b) { b.insert(u); b.insert(v); return b; }
} a[(N + N) * 4], di[N];

namespace seg {

int n, col[N + N];
diam bu[N + N];
void build(int u, int l, int r) {
   if(l == r) { a[u] = bu[l]; return ; }
   int mid = (l + r) >> 1; build(u << 1, l, mid); build(u << 1 | 1, mid + 1, r); a[u] = a[u << 1] + a[u << 1 | 1];
}
void modify(int u, int l, int r, int p, int v) {
   if(l == r) { a[u] = {v, v, 0}; return ; }
   int mid = (l + r) >> 1;
   p <= mid ? modify(u << 1, l, mid, p, v) : modify(u << 1 | 1, mid + 1, r, p, v);
   if(col[l] == col[r]) a[u] = a[u << 1] + a[u << 1 | 1];
}
diam query(int u, int l, int r, int ql, int qr) {
   if(l == ql && r == qr) return a[u];
   int mid = (l + r) >> 1;
   if(qr <= mid) return query(u << 1, l, mid, ql, qr);
   if(ql > mid) return query(u << 1 | 1, mid + 1, r, ql, qr);
   return query(u << 1, l, mid, ql, mid) + query(u << 1 | 1, mid + 1, r, mid + 1, qr);
}

}

diam qd(int col) {
   return seg::query(1, 1, seg::n, siz[col - 1] + 1, siz[col]);
}

namespace DFN {

ll sd[N << 2], s[N << 2], a1[N << 2], a2[N << 2];
//s1 * dis + s2
void build(int u, int l, int r) {
   if(l == r) { sd[u] = dis[ID[l]]; return ; }
   int mid = (l + r) >> 1;
   build(u << 1, l, mid); build(u << 1 | 1, mid + 1, r); sd[u] = sd[u << 1] + sd[u << 1 | 1];
}
//a[u] += x*dis[u] + y
void addtag(int u, int l, int r, ll x, ll y) {
   s[u] += x * sd[u] + y * (r - l + 1ll); a1[u] += x; a2[u] += y;
}
void pd(int u, int l, int r) {
   if(a1[u] || a2[u]) {
      int mid = (l + r) >> 1;
      addtag(u << 1, l, mid, a1[u], a2[u]);
      addtag(u << 1 | 1, mid + 1, r, a1[u], a2[u]);
      a1[u] = a2[u] = 0;
   }
}
void modify(int u, int l, int r, int ql, int qr, ll x, ll y) {
   if(l == ql && r == qr) { addtag(u, l, r, x, y); return; }
   int mid = (l + r) >> 1; pd(u, l, r);
   if(qr <= mid) modify(u << 1, l, mid, ql, qr, x, y);
   else if(ql > mid) modify(u << 1 | 1, mid + 1, r, ql, qr, x, y);
   else {
      modify(u << 1, l, mid, ql, mid, x, y);
      modify(u << 1 | 1, mid + 1, r, mid + 1, qr, x, y);
   }
   s[u] = s[u << 1] + s[u << 1 | 1];
}
ll query(int u, int l, int r, int ql, int qr) {
   if(l == ql && r == qr) return s[u];
   int mid = (l + r) >> 1; pd(u, l, r);
   if(qr <= mid) return query(u << 1, l, mid, ql, qr);
   if(ql > mid) return query(u << 1 | 1, mid + 1, r, ql, qr);
   return query(u << 1, l, mid, ql, mid) + query(u << 1 | 1, mid + 1, r, mid + 1, qr);
}

}
namespace chn {

ll s[N << 2], a1[N << 2];
int sd[N << 2];
void build(int u, int l, int r) {
   if(l == r) { sd[u] = -2 * len[ID[l]]; return ; }
   int mid = (l + r) >> 1;
   build(u << 1, l, mid); build(u << 1 | 1, mid + 1, r); sd[u] = sd[u << 1] + sd[u << 1 | 1];
}
//a[u] += x*(-2len[u]) + y
void addtag(int u, ll x) { s[u] += x * sd[u]; a1[u] += x; }
void pd(int u) {
   if(a1[u]) {
      addtag(u << 1, a1[u]);
      addtag(u << 1 | 1, a1[u]);
      a1[u] = 0;
   }
}
void modify(int u, int l, int r, int ql, int qr, ll x) {
   if(l == ql && r == qr) { addtag(u, x); return ; }
   int mid = (l + r) >> 1; pd(u);
   if(qr <= mid) modify(u << 1, l, mid, ql, qr, x);
   else if(ql > mid) modify(u << 1 | 1, mid + 1, r, ql, qr, x);
   else {
      modify(u << 1, l, mid, ql, mid, x);
      modify(u << 1 | 1, mid + 1, r, mid + 1, qr, x);
   }
   s[u] = s[u << 1] + s[u << 1 | 1];
}
ll query(int u, int l, int r, int ql, int qr) {
   if(l == ql && r == qr) return s[u];
   int mid = (l + r) >> 1; pd(u);
   if(qr <= mid) return query(u << 1, l, mid, ql, qr);
   if(ql > mid) return query(u << 1 | 1, mid + 1, r, ql, qr);
   return query(u << 1, l, mid, ql, mid) + query(u << 1 | 1, mid + 1, r, mid + 1, qr);
}

}
struct BIT {
   ll bit[N];
   void add(int u, ll v) {
      if(u == 0) return ;
      for(; u <= n; u += u & (-u)) bit[u] += v;
   }
   ll qry(int u) {
      ll ans = 0;
      for(; u >= 1; u &= u - 1) ans += bit[u];
      return ans;
   }
   ll qry(int u, int v) { return u > v ? 0ll : qry(v) - qry(u - 1); }
} b[2]; //0:cnt
void workin(int u, int c, int x, int w) { //subtree += w*dis(i, c)
   DFN::modify(1, 1, n, dl[u], dr[u], w, w * (-2 * dis[x] + dis[c]));
}
//W[u] = -2 len[u], i\in[1, u], subtree(i) += W[u]
void tree(int u, int w) {
   while(top[u] ^ 1) {
      chn::modify(1, 1, n, dl[top[u]], dl[u], w);
      u = fa[top[u]];
   }
   chn::modify(1, 1, n, 1, dl[u], w);
}
ll Qtree(int u) {
   ll ans = 0;
   while(top[u] ^ 1) {
      ans += chn::query(1, 1, n, dl[top[u]], dl[u]);
      u = fa[top[u]];
   }
   return ans += chn::query(1, 1, n, 1, dl[u]);
}
void add(int u, int w) {
   tree(u, w); b[0].add(dl[u], w); b[1].add(dl[u], w * val[u]);
}
void workout(int u, int c, int w) {
   if(u == 1) return ;
   DFN::modify(1, 1, n, 1, n, w, w * dis[c]);
   DFN::modify(1, 1, n, dl[u], dr[u], - w, - w * dis[c] + w * 2 * dis[fa[u]]);
   add(fa[u], w);
}
void work(diam D, int w) {
   int u = D.u, v = D.v;
   if(u == v) {
      workin(u, u, u, w); workout(u, u, w);
   } else {
      int x = LCA::get(u, v);
      if(dist2(u, x) < dist2(v, x)) swap(u, v);
      int y = u;
      for(int i = 16; i >= 0; i --) { //y close to u
         int z = f[y][i];
         if(z && dist2(u, z) * 2 < D.d) y = z;
      }
      workin(y, v, x, w); workout(y, u, w);
   }
}
int main() {
   read(n); read(m); read(q);
   rep(i, 1, n) read(c[i]), siz[c[i]] ++;
   rep(i, 2, n) read(fa[i]), G[fa[i]].pb(i);
   rep(i, 2, n) read(len[i]);
   dfs(1); dfs2(1, 1); LCA::build(); DFN::build(1, 1, n); chn::build(1, 1, n);
   rep(i, 1, n) val[i] = val[fa[i]] - 2ll * len[i] * sz[i];
   rep(i, 1, q) {
      read(op[i]); read(qu[i]);
      if(op[i] == 1) {
         read(qv[i]);
         siz[qv[i]] ++;
      }
   }
   rep(i, 1, m) {
      siz[i] += siz[i - 1];
      for(int j = siz[i - 1] + 1; j <= siz[i]; j ++) seg::col[j] = i;
   }
   seg::n = siz[m];
   rep(i, 1, n) {
      pos[i] = siz[c[i] - 1] + (++ cur[c[i]]);
      seg::bu[ pos[i] ] = {i, i, 0};
   }
   seg::build(1, 1, seg::n);
   rep(i, 1, m) work(di[i] = qd(i), 1);
   rep(i, 1, q) {
      int u = qu[i], v = qv[i];
      if(op[i] == 1) {
         if(c[u] == v) continue ;
         auto t1 = di[c[u]], t2 = di[v];
         // work(di[c[u]], -1); work(di[v], -1);
         seg::modify(1, 1, seg::n, pos[u], 0);
         pos[u] = siz[v - 1] + (++ cur[v]);
         seg::modify(1, 1, seg::n, pos[u], u);

         di[c[u]] = qd(c[u]); di[v] = qd(v);
         if(!(t1 == di[c[u]])) {
            work(t1, -1); work(di[c[u]], 1);
         }
         if(!(t2 == di[v])) {
            work(t2, -1); work(di[v], 1);
         }
         c[u] = v;
      } else {
         ll ans = DFN::query(1, 1, n, dl[u], dr[u]);
         ans += Qtree(u) * sz[u];
         ans -= b[0].qry(dl[u] + 1, dr[u]) * val[u];
         ans += b[1].qry(dl[u] + 1, dr[u]);
         printf("%lld\n", ans);
      }
   }
   
   return 0;
}
/*
5 2 3
1 1 1 2 2
1 2 2 1
1 1 1 1
1 1 2
1 2 2
1 5 1

8 3 1
1 2 3 1 3 2 2 3
1 2 2 1 5 6 4
1 1 1 1 1 1 1
2 5

*/