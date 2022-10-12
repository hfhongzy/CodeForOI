//idea from skip2004
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
int ch[N][2], fa[N], w[N], tag[N];
inline int dir(int u) {
  return ch[fa[u]][0] == u ? 0 : (ch[fa[u]][1] == u ? 1 : -1);
}
void down(int u) {
  int &ls = ch[u][0], &rs = ch[u][1];
  if(tag[u]) { tag[ls] = tag[rs] = w[ls] = w[rs] = tag[u]; tag[u] = 0; }
}
void rotate(int u) {
  int d = dir(u), f = fa[u];
  if(fa[u] = fa[f], ~dir(f)) ch[fa[u]][dir(f)] = u;
  if(ch[f][d] = ch[u][d ^ 1], ch[f][d]) fa[ch[f][d]] = f;
  ch[u][d ^ 1] = f; fa[f] = u;
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
  int c[N];
  void add(int u, int v) {
    u = n - u + 1;
    for(; u <= n; u += u & (-u)) c[u] = max(c[u], v);
  }
  int qry(int u) {
    u = n - u + 1;
    int ans = 0;
    for(; u; u &= u - 1) ans = max(ans, c[u]);
    return ans;
  }
} bit;
void access(int u, int pos) {
  int v;
  for(v = 0; u; v = u, u = fa[u]) {
    splay(u);
    if(w[u]) bit.add(w[u], SAM::len[u]);
    ch[u][1] = v;
  }
  tag[v] = w[v] = pos;
}
struct node {
  int l, r, id;
  bool operator < (const node &b) const {
    return r < b.r;
  }
} qs[N];
int ans[N];
int main() {
  scanf("%d%d%s", &n, &m, s + 1);
  SAM::init();
  static int cur[N];
  rep(i, 1, n) SAM::extend(s[i] - 'a'), cur[i] = SAM::la;
  rep(i, 1, m) { scanf("%d%d", &qs[i].l, &qs[i].r); qs[i].id = i; }
  sort(qs + 1, qs + m + 1);
  rep(i, 2, SAM::id) { fa[i] = SAM::lnk[i]; tag[i] = w[i] = 0; }
  int p = 0;
  rep(r, 1, n) {
    access(cur[r], r);
    while(p < m && qs[p + 1].r == r) {
      ++ p;
      int l = qs[p].l;
      int ql = 1, qr = r - l + 1, lcs = 0;
      while(ql <= qr) {
        int mid = (ql + qr) >> 1;
        if(bit.qry(l + mid - 1) >= mid) ql = (lcs = mid) + 1;
        else qr = mid - 1;
      }
      ans[qs[p].id] = r - l + 1 - lcs;
    }
  }
  rep(i, 1, m) printf("%d\n", ans[i]);
  return 0;
}