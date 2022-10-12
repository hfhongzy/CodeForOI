#include <bits/stdc++.h>
#define fs first
#define sc second
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 3e5 + 10;
int n, m, ch[N][2], fa[N];
uint tag[N], val[N];
bool rev[N];
int dir(int u) { return ch[fa[u]][0] == u ? 0 : (ch[fa[u]][1] == u ? 1 : -1); }
void rotate(int u) {
  int f = fa[u], d = dir(u);
  if(fa[u] = fa[f], ~ dir(f)) ch[fa[f]][dir(f)] = u;
  if((ch[f][d] = ch[u][d ^ 1]) > 0) fa[ch[u][d ^ 1]] = f;
  ch[u][d ^ 1] = f; fa[f] = u;
}
void addt(int u, uint t) {
  if(u) { tag[u] ^= t; val[u] ^= t; }
}
void pushd(int u) {
  int &ls = ch[u][0], &rs = ch[u][1];
  uint t;
  if(rev[u]) { swap(ls, rs); rev[ls] ^= 1; rev[rs] ^= 1; rev[u] = 0; }
  if((t = tag[u]) > 0) { addt(ls, t); addt(rs, t); tag[u] = 0; }
}
int st[N];
void splay(int u) {
  int t = 0, v;
  for(v = u; ~ dir(v); v = fa[v]) st[t ++] = v;
  for(pushd(v); t --; pushd(st[t])) ;
  for(; ~ dir(u); rotate(u)) if(~ dir(fa[u]))
    rotate(dir(u) == dir(fa[u]) ? fa[u] : u);
}
void access(int u) {
  for(int v = 0; u; v = u, u = fa[u]) {
    splay(u); ch[u][1] = v;
  }
}
void mkroot(int u) {
  access(u); splay(u); rev[u] ^= 1;
}
void link(int u, int v) {
  if(u == v) return ;
  mkroot(u); access(v); splay(v);
  if(!fa[u]) fa[u] = v;
}
void cut(int u, int v) {
  if(u == v) return ;
  mkroot(u); access(v); splay(v);
  if(ch[v][0] == u) {
    ch[v][0] = fa[u] = 0;
  }
}
void split(int u, int v) {
  mkroot(u); access(v); splay(u);
}
unordered_map<ll, int> ID;
ll H(int x, int y) {
  if(x > y) swap(x, y);
  return (ll)x * N + y;
}
mt19937 mt(time(0));
int eu[N], ev[N], c;
uint ew[N], all;
void path_xor(int u, int v, uint w) {
  split(u, v); addt(u, w); //pushd(u);
}
int main() {
  scanf("%*d%d%d", &n, &m);
  int op, x, y, u, v;
  rep(i, 1, n - 1) {
    scanf("%d%d", &x, &y);
    link(x, n + i); link(n + i, y);
    ID[H(x, y)] = n + i;
  }
  rep(i, 1, m) {
    // cerr << "i = " << i << endl;
    scanf("%d%d", &op, &x);
    if(op == 1) {
      scanf("%d%d%d", &y, &u, &v);
      ll h0 = H(x, y); int id = ID[h0]; splay(id); uint k = val[id]; val[id] = 0; path_xor(u, v, k);
      cut(id, x); cut(id, y);
      ll h = H(u, v); ID[h] = id;
      link(id, u); link(id, v);
    }
    if(op == 2) {
      scanf("%d", &y);
      ew[++ c] = mt(); eu[c] = x; ev[c] = y; all ^= ew[c];
      path_xor(x, y, ew[c]);
    }
    if(op == 3) {
      int u = eu[x], v = ev[x]; all ^= ew[x];
      path_xor(u, v, ew[x]);
    }
    if(op == 4) {
      scanf("%d", &y);
      int id = ID[H(x, y)];
      splay(id);
      puts(all == val[id] ? "YES" : "NO");
    }
  }
  return 0;
}