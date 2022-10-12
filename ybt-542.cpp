#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 4e5 + 10;
const int M = N * 64;
int la, id, lnk[N], len[N], edp[N], ch[N][26], w[N], bit[N];
vector<int> G[N];
void init() {
  lnk[0] = -1; id = la = 0; fill(ch[0], ch[0] + 26, -1);
}
void extend(int c) {
  int u = ++ id, p = la;
  fill(ch[u], ch[u] + 26, -1); len[u] = len[la] + 1;
  for(; ~ p && ch[p][c] == -1; p = lnk[p]) ch[p][c] = u;
  if(p == -1) lnk[u] = 0;
  else {
    int q = ch[p][c];
    if(len[q] == len[p] + 1) lnk[u] = q;
    else {
      int q0 = ++ id;
      copy(ch[q], ch[q] + 26, ch[q0]);
      len[q0] = len[p] + 1; lnk[q0] = lnk[q];
      lnk[u] = lnk[q] = q0;
      for(; ~ p && ch[p][c] == q; p = lnk[p])
        ch[p][c] = q0;
    }
  }
  la = u; w[u] = 1; edp[u] = len[u];
}
int rt[N], ls[M], rs[M], sz[M], seg_id;
void insert(int &u, int l, int r, int x) {
  u = ++ seg_id; sz[u] = 1;
  if(l == r) return ;
  int mid = (l + r) >> 1;
  if(x <= mid) {
    insert(ls[u], l, mid, x);
  } else {
    insert(rs[u], mid + 1, r, x);
  }
}
int query(int u, int l, int r, int ql, int qr) {
  if(l == ql && r == qr) return sz[u];
  int mid = (l + r) >> 1;
  if(qr <= mid) return query(ls[u], l, mid, ql, qr);
  if(ql > mid) return query(rs[u], mid + 1, r, ql, qr);
  return query(ls[u], l, mid, ql, mid) + query(rs[u], mid + 1, r, mid + 1, qr);
}
int smerge(int u, int v) {
  if(!u && !v) return 0;
  int x = ++ seg_id;
  if(!u || !v) {
    sz[x] = sz[u] | sz[v];
    ls[x] = ls[u] | ls[v];
    rs[x] = rs[u] | rs[v];
    return x;
  }
  sz[x] = sz[u] + sz[v];
  ls[x] = smerge(ls[u], ls[v]);
  rs[x] = smerge(rs[u], rs[v]);
  return x;
}
int cnt[N], ord[N];
void build(int n) {
  rep(i, 1, id) cnt[len[i]] ++;
  rep(i, 1, n) cnt[i] += cnt[i - 1];
  rep(i, 1, id) ord[cnt[len[i]] --] = i;
  per(i, id, 1) {
    int u = ord[i];
    if(!edp[lnk[u]]) {
      edp[lnk[u]] = edp[u];
    }
  }
}

char s[N];
int n, dp[N];
void dfs(int u) {
  if(w[u]) insert(rt[u], 1, n, edp[u]);
  for(int v : G[u]) {
    dfs(v);
    rt[u] = smerge(rt[u], rt[v]);
  }
}
int inc(int u, int v) { //u >= v
  int pl = edp[v] - len[v] + 1 + len[u] - 1, pr = edp[v];
  return query(rt[u], 1, n, pl, pr) >= 2;
}
void dfs2(int u, int t = 0) {
  if(u) {
    if(!t) dp[u] = 1;
    else {
      dp[u] = dp[t] + inc(t, u);
    }
    if(dp[u] > dp[t]) t = u;
  }
  for(int v : G[u]) {
    dfs2(v, t);
  }
}
int main() {
 freopen("level.in", "r", stdin);
 freopen("level.out", "w", stdout);
  scanf("%s", s + 1);
  n = strlen(s + 1);
  init();
  rep(i, 1, n) extend(s[i] - 'a');
  build(n);
  rep(i, 1, id) G[lnk[i]].pb(i);
  dfs(0); dfs2(0);
  int ans = 0;
  rep(i, 1, id) {
    ans = max(ans, dp[i] + (sz[rt[i]] >= 2));
  }
  printf("%d\n", ans);
  return 0;
}