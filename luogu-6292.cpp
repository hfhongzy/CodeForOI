#include <bits/stdc++.h>
#define LOG(FMT...) fprintf(stderr, FMT)
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 2e5 + 20;
int n, m;
char s[N];
//SAM
namespace SAM {

int ch[N][26], lnk[N], len[N], la, id;
void init() { id = la = 1; lnk[1] = 0; }
void extend(int c) {
  int u = ++ id, p = la; len[u] = len[la] + 1;
  for(; p && !ch[p][c]; p = lnk[p]) ch[p][c] = u;
  if(!p) lnk[u] = 1;
  else {
    int q = ch[p][c];
    if(len[q] == len[p] + 1) lnk[u] = q;
    else {
      int q0 = ++ id; copy(ch[q], ch[q] + 26, ch[q0]);
      len[q0] = len[p] + 1; lnk[q0] = lnk[q];
      lnk[u] = lnk[q] = q0;
      for(; p && ch[p][c] == q; p = lnk[p]) ch[p][c] = q0;
    }
  }
  la = u;
}

}
//LCT
int ch[N][2], fa[N], sum[N], w[N], tag[N];
inline int dir(int u) {
  return ch[fa[u]][0] == u ? 0 : (ch[fa[u]][1] == u ? 1 : -1);
}
void rotate(int u) {
  int d = dir(u), f = fa[u];
  if(fa[u] = fa[f], ~dir(f)) ch[fa[u]][dir(f)] = u;
  if(ch[f][d] = ch[u][d ^ 1], ch[f][d]) fa[ch[f][d]] = f;
  ch[u][d ^ 1] = f; fa[f] = u;
}
void down(int u) {
  int &ls = ch[u][0], &rs = ch[u][1];
  if(tag[u]) { tag[ls] = tag[rs] = w[ls] = w[rs] = tag[u]; tag[u] = 0; }
}
int st[N];
void splay(int u) {
  int top = 0;
  for(int v = u; ~dir(v); v = fa[v]) st[top ++] = fa[v];
  while(top --) down(st[top]);
  down(u);
  for(; ~dir(u); rotate(u)) if(~dir(fa[u]))
    rotate(dir(u) == dir(fa[u]) ? fa[u] : u);
}
struct BIT {
  ll s, s2, c[N], d[N];
  void add(int u, ll x) {
    if(!u) return ;
    s += x;
    for(int i = u; i <= n; i += i & (-i)) c[i] += x;
    x *= u; s2 += x;
    for(int i = u; i <= n; i += i & (-i)) d[i] += x;
  }
  ll qry(int u) {
    ll z = s;
    for(int i = u; i; i &= i - 1) z -= c[i];
    z *= u;
    for(int i = u; i; i &= i - 1) z += d[i];
    return z;
  }
  void add(int l, int r, int x) { add(r, x); add(l - 1, -x); }
  ll qry(int l, int r) {
    return s2 - qry(l - 1);
    // return qry(r) - qry(l - 1);
  }
} bit;
struct node {
  int l, r, id;
  bool operator < (const node &b) const {
    return r < b.r;
  }
} qs[N];
ll ans[N];
void access(int u, int r) {
  int v;
  for(v = 0; u; v = u, u = fa[u]) {
    splay(u); ch[u][1] = v;
    if(w[u])
      bit.add(w[u] - SAM::len[u] + 1, w[u] - (SAM::len[fa[u]] + 1) + 1, -1);
  }
  tag[v] = w[v] = r;
  bit.add(1, r, 1);
}
int main() {
  scanf("%s", s + 1);
  n = strlen(s + 1);
  SAM::init();
  static int cur[N];
  rep(i, 1, n) SAM::extend(s[i] - 'a'), cur[i] = SAM::la;
  scanf("%d", &m);
  rep(i, 1, m) {
    scanf("%d%d", &qs[i].l, &qs[i].r); qs[i].id = i;
  }
  sort(qs + 1, qs + m + 1);
  rep(i, 2, SAM::id) { fa[i] = SAM::lnk[i]; tag[i] = w[i] = 0; }
  int p = 0;
  rep(r, 1, n) {
    access(cur[r], r);
    while(p < m && qs[p + 1].r == r) {
      ++ p;
      ans[qs[p].id] = bit.qry(qs[p].l, r);
    }
  }
  rep(i, 1, m) printf("%lld\n", ans[i]);
  return 0;
}