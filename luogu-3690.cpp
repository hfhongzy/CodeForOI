#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 1e5 + 10;
int n, m, a[N], w[N], fa[N], ch[N][2];
bool rev[N];
int dir(int u) { return ch[fa[u]][0] == u ? 0 : (ch[fa[u]][1] == u ? 1 : -1); }
void upd(int u) { w[u] = w[ch[u][0]] ^ w[ch[u][1]] ^ a[u]; }
void rot(int u) {
  int f = fa[u], d = dir(u);
  if(fa[u] = fa[f], ~dir(f)) ch[fa[u]][dir(f)] = u;
  if(bool(ch[f][d] = ch[u][d ^ 1])) fa[ch[f][d]] = f;
  ch[u][d ^ 1] = f; fa[f] = u; upd(f);
}
int st[N], top;
void down(int u) {
  if(rev[u]) {
    int &ls = ch[u][0], &rs = ch[u][1];
    rev[ls] ^= 1; rev[rs] ^= 1; swap(ls, rs); rev[u] = 0;
  }
}
void splay(int u) {
  top = 0;
  for(int v = u; ~dir(v); v = fa[v])
    st[top ++] = fa[v];
  while(top --) down(st[top]);
  down(u);
  for(; ~dir(u); rot(u)) if(~dir(fa[u]))
    rot(dir(u) == dir(fa[u]) ? fa[u] : u);
  upd(u);
}
void access(int u) {
  for(int v = 0; u; v = u, u = fa[u]) {
    splay(u); ch[u][1] = v; upd(v);
  }
}
void mkroot(int u) {
  access(u); splay(u); rev[u] ^= 1;
}
void link(int u, int v) {
  mkroot(u); access(v); splay(v);
  if(!fa[u]) fa[u] = v;
} 
void cut(int u, int v) {
  mkroot(u); access(v); splay(v);
  if(ch[v][0] == u) {
    ch[v][0] = fa[u] = 0; upd(v);
  }
}
void split(int u, int v) {
  mkroot(u); access(v); splay(v);
}
int main() {
  scanf("%d%d", &n, &m);
  rep(i, 1, n) scanf("%d", a + i), w[i] = a[i];
  int op, x, y;
  rep(T, 1, m) {
    scanf("%d%d%d", &op, &x, &y);
    if(op == 0) { split(x, y); printf("%d\n", w[y]); }
    if(op == 1) link(x, y);
    if(op == 2) cut(x, y);
    if(op == 3) { splay(x); a[x] = y; upd(x); }
  }
  return 0;
}