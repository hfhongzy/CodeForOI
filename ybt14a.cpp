#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 4e5 + 5;
const int INF = 1 << 30;

#define ls ch[u][0]
#define rs ch[u][1]
int w[N], Min[N], fa[N], ch[N][2];
bool rev[N];
int dir(int u) { return ch[fa[u]][0] == u ? 0 : (ch[fa[u]][1] == u ? 1 : -1); }
void upd(int u) {
  Min[u] = w[u];
  if(ls) Min[u] = min(Min[u], Min[ls]);
  if(rs) Min[u] = min(Min[u], Min[rs]);
}
void rot(int u) {
  int f = fa[u], d = dir(u);
  if(fa[u] = fa[f], ~ dir(f)) ch[fa[f]][dir(f)] = u;
  if((ch[f][d] = ch[u][d ^ 1]) > 0) fa[ch[u][d ^ 1]] = f;
  ch[u][d ^ 1] = f; fa[f] = u; upd(f);
}
void pd(int u) {
  if(rev[u]) { swap(ls, rs); rev[ls] ^= 1; rev[rs] ^= 1; rev[u] = 0; }
}
int st[N];
void splay(int u) {
  int t = 0, v;
  for(v = u; ~ dir(v); v = fa[v]) st[t ++] = v;
  for(pd(v); t --; pd(st[t])) ;
  for(; ~ dir(u); rot(u)) if(~ dir(fa[u]))
    rot(dir(u) == dir(fa[u]) ? fa[u] : u);
  upd(u);
}
void access(int u) {
  for(int v = 0; u; v = u, u = fa[u]) {
    splay(u); ch[u][1] = v; upd(u);
  }
}
void mkroot(int u) {
  access(u); splay(u); rev[u] ^= 1;
}
void link(int u, int v) {
  mkroot(u); access(v); splay(v);
  // assert(!fa[u]);
  fa[u] = v;
}
void cut(int u, int v) {
  mkroot(u); access(v); splay(v);
  // assert(ch[v][0] == u);
  ch[v][0] = fa[u] = 0; upd(v);
}

#undef ls
#undef rs

struct node { int l, r, id; } a[N];
int n, m, q, eu[N], ev[N], ans[N], cnt;

namespace bit {

int c[N];
void add(int x, int y) {
  for(; x <= m; x += x & (-x))
    c[x] += y;
}
int qry(int x) {
  int ans = 0;
  for(; x >= 1; x &= x - 1)
    ans += c[x];
  return ans;
}

}
int main() {
  freopen("graph.in", "r", stdin);
  freopen("graph.out", "w", stdout);
  scanf("%d%d%d", &n, &m, &q);
  rep(i, 1, m) scanf("%d%d", eu + i, ev + i);
  rep(i, 1, q) {
    scanf("%d%d", &a[i].l, &a[i].r);
    a[i].id = i;
  }
  rep(i, 1, n + m) Min[i] = w[i] = i <= n ? INF : i - n;
  sort(a + 1, a + q + 1, [&](node x, node y) {
    return x.r < y.r;
  });
  int p = 0;
  rep(i, 1, m) {
    int u = eu[i], v = ev[i];
    if(u != v) {
      mkroot(u); access(v); splay(v);
      if(!fa[u]) {
        link(u, n + i); link(n + i, v); cnt ++;
      } else {
        int z = Min[v];
        // assert(1 <= z && z < i);
        cut(eu[z], n + z); cut(n + z, ev[z]); bit::add(z, -1);
        link(u, n + i); link(n + i, v);
      }
      bit::add(i, 1);
    }
    while(a[p + 1].r == i) {
      p ++;
      ans[a[p].id] = n - (cnt - bit::qry(a[p].l - 1));
    }
  }
  rep(i, 1, q) printf("%d\n", ans[i]);
  return 0;
}
