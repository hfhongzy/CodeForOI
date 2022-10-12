#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
char gc() {
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
const int N = 5e5 + 10;
const int M = N * 32;
struct node {
  int x, p, w;
  bool operator == (const node &b) const {
    return x == b.x && p == b.p;
  }
} a[N * 2];
int n, m, q, rt[N], id, w[M], ls[M], rs[M], lnk[M];
void build(int &u, int l, int r) {
  u = ++ id;
  if(l == r) return ;
  int mid = (l + r) >> 1;
  build(ls[u], l, mid);
  build(rs[u], mid + 1, r);
}
void update(int &u, int p, int l, int r, int x, int y) {
  u = ++ id; lnk[u] = p;
  if(l == r) { w[u] = y; return ; }
  int mid = (l + r) >> 1;
  if(x <= mid) {
    rs[u] = rs[p];
    update(ls[u], ls[p], l, mid, x, y);
  } else {
    ls[u] = ls[p];
    update(rs[u], rs[p], mid + 1, r, x, y);
  }
}
int vec[N], seq[N], s[N], cnt[N], t[N], L[N], R[N], ord[N];
void dfs(int u, int l, int r) {
  if(l < r) {
    int mid = (l + r) >> 1;
    dfs(ls[u], l, mid);
    dfs(rs[u], mid + 1, r);
  }
  vec[++ *vec] = u;
}
int main() {
  read(n); read(m); read(q);
  int l, r, p, b;
  rep(i, 1, q) {
    read(l); read(r); read(p); read(b);
    a[2 * i - 1] = {l, p, b};
    a[2 * i] = {r + 1, p, 0};
  }
  sort(a + 1, a + 2 * q + 1, [&](node a, node b) {
    return a.x == b.x ? (a.p == b.p ? a.w < b.w : a.p < b.p) : a.x < b.x;
  });
  build(rt[0], 1, m);
  int j = 0;
  rep(i, 1, n) {
    rt[i] = rt[i - 1];
    while(a[j + 1].x == i) {
      j ++;
      if(!(a[j] == a[j + 1])) {
        update(rt[i], rt[i], 1, m, a[j].p, a[j].w);
      }
    }
  }
  dfs(rt[n], 1, m);
  rep(T, 1, vec[0]) {
    int u = vec[T], sz = 0, mx = 0;
    if(!ls[u]) {
      int c = 0;
      for(int v = u; v; v = lnk[v]) seq[++ c] = w[v];
      sort(seq + 1, seq + c + 1);
      c = unique(seq + 1, seq + c + 1) - seq - 1;
      for(int v = u; v; v = lnk[v]) w[v] = lower_bound(seq + 1, seq + c + 1, w[v]) - seq;
      continue ;
    }
    for(int v = u; v; v = lnk[v]) {
      s[++ sz] = v;
      mx = max(mx, max(L[sz] = w[ls[v]], R[sz] = w[rs[v]]));
    }
    fill(cnt + 1, cnt + mx + 1, 0);
    rep(i, 1, sz) cnt[R[i]] ++;
    rep(i, 1, mx) cnt[i] += cnt[i - 1];
    rep(i, 1, sz) t[cnt[R[i]] --] = i;

    fill(cnt + 1, cnt + mx + 1, 0);
    rep(i, 1, sz) cnt[L[i]] ++;
    rep(i, 1, mx) cnt[i] += cnt[i - 1];
    per(i, sz, 1) ord[cnt[L[t[i]]] --] = t[i];
    int rk = 1; w[s[ord[1]]] = 1;
    rep(i, 2, sz) {
      if(!(L[ord[i]] == L[ord[i - 1]] && R[ord[i]] == R[ord[i - 1]])) {
        rk ++;
      }
      w[s[ord[i]]] = rk;
    }
  }
  static int ans[N];
  rep(i, 1, n) ans[i] = i;
  stable_sort(ans + 1, ans + n + 1, [&](int x, int y) { return w[rt[x]] < w[rt[y]]; });
  rep(i, 1, n) printf("%d\n", ans[i]);
  return 0;
}