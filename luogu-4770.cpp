#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
using ll = long long;
const int N = 1e6 + 10;
const int M = N * 40;

struct SAM {
  int ch[N][26], fa[N], len[N], pos[N], id, la;
  void clr(int u) { fill(ch[u], ch[u] + 26, 0); }
  void init() { id = la = 1; clr(1); }
  void append(int c) {
    int u = ++ id, p = la; clr(u); len[u] = len[la] + 1;
    for(; p && !ch[p][c]; p = fa[p]) ch[p][c] = u;
    if(!p) fa[u] = 1;
    else {
      int q = ch[p][c];
      if(len[p] + 1 == len[q]) fa[u] = q;
      else {
        int q0 = ++ id; len[q0] = len[p] + 1; fa[q0] = fa[q];
        copy(ch[q], ch[q] + 26, ch[q0]);
        fa[q] = fa[u] = q0;
        for(; p && ch[p][c] == q; p = fa[p]) ch[p][c] = q0;
      }
    }
    la = u; pos[u] = len[u];
  }
  int cnt[N], ord[N];
  void build(int n) {
    rep(i, 0, n) cnt[i] = 0;
    rep(i, 1, id) cnt[len[i]] ++;
    rep(i, 1, n) cnt[i] += cnt[i - 1];
    rep(i, 1, id) ord[cnt[len[i]] --] = i;
  }
} S, T;
char s[N], t[N];
int n, m;
int rt[N], sz[M], ls[M], rs[M], id;
void insert(int &u, int l, int r, int p) {
  if(!u) u = ++ id;
  sz[u] ++;
  if(l == r) return ;
  int mid = (l + r) >> 1;
  if(p <= mid) insert(ls[u], l, mid, p);
  else insert(rs[u], mid + 1, r, p);
}
int cpy(int v) {
  if(!v) return 0;
  ++ id; sz[id] = sz[v]; ls[id] = ls[v]; rs[id] = rs[v];
  return id;
}
int merge(int u, int v) {
  if(!u || !v) return cpy(u | v);
  int w = ++ id; sz[w] = sz[u] + sz[v];
  ls[w] = merge(ls[u], ls[v]);
  rs[w] = merge(rs[u], rs[v]);
  return w;
}
bool query(int u, int l, int r, int ql, int qr) {
  if(!u || (l == ql && r == qr)) return sz[u] >= 1;
  int mid = (l + r) >> 1;
  if(qr <= mid) return query(ls[u], l, mid, ql, qr);
  if(ql > mid) return query(rs[u], mid + 1, r, ql, qr);
  return query(ls[u], l, mid, ql, mid) || query(rs[u], mid + 1, r, mid + 1, qr);
}
int cur;
void flast(int u, int l, int r, int p) {
  if(~cur || l > p || !sz[u]) return ;
  if(l == r) { cur = l; return ; }
  int mid = (l + r) >> 1;
  flast(rs[u], mid + 1, r, p);
  flast(ls[u], l, mid, p);
}
int main() {
  int test;
  scanf("%s%d", s + 1, &test);
  n = strlen(s + 1);
  S.init();
  rep(i, 1, n) S.append(s[i] -= 'a');
  S.build(n);
  per(i, S.id, 1) {
    int u = S.ord[i];
    if(S.pos[u])
      insert(rt[u], 1, n, S.pos[u]);
    if(S.fa[u])
      rt[S.fa[u]] = merge(rt[S.fa[u]], rt[u]);
  }
  int l, r;
  rep(_, 1, test) {
    scanf("%s%d%d", t + 1, &l, &r);
    m = strlen(t + 1);
    T.init();
    rep(i, 1, m) T.append(t[i] -= 'a');
    T.build(m);
    per(i, T.id, 1) { int u = T.ord[i]; T.pos[ T.fa[u] ] = T.pos[u]; }
    static int mat[N];
    auto valid = [&](int u) {
      return query(rt[u], 1, n, l + S.len[S.fa[u]], r);
    };
    int u = 1, len = 0;
    rep(i, 1, m) {
      while(u > 1 && !S.ch[u][t[i]]) u = S.fa[u], len = S.len[u];
      if(!S.ch[u][t[i]]) { mat[i] = len = 0; continue ; }
      u = S.ch[u][t[i]]; len ++;
      while(u > 1 && !valid(u)) u = S.fa[u], len = S.len[u];
      if(u == 1) { mat[i] = len = 0; continue ; }

      cur = -1; flast(rt[u], 1, n, r); mat[i] = min(len, cur - l + 1);
    }
    ll ans = 0;
    rep(u, 2, T.id)
      ans += max(0, T.len[u] - max(T.len[T.fa[u]], mat[T.pos[u]]));
    printf("%lld\n", ans);
  }
  return 0;
}
/*
scbamgepe
1
sgepe 1 9
*/