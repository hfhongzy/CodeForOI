#include <bits/stdc++.h>
#define pb push_back
#define LOG(FMT...) fprintf(stderr, FMT);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
template<class T>
void chkmax(T &x, const T &y) { if(x < y) x = y; }
const int N = 2e5 + 10;
int n, a[N];
vector<int> G[N];

namespace task1 {

const int N = 4010;
int sz[N][N], d[N][N], ans[N];
void dfs(int u, int *s, int *d, int fa = 0) {
  s[u] = 1; d[u] = d[fa] + 1;
  for(int v : G[u]) if(v ^ fa) {
    dfs(v, s, d, u);
    s[u] += s[v];
  }
}
void main() {
  rep(i, 1, n) {
    dfs(i, sz[i], d[i]);
  }
  rep(i, 1, n) rep(j, i + 1, n) {
    chkmax(ans[min(sz[i][j], sz[j][i])], d[i][j]);
  }
  ans[n / 2 + 1] = 1;
  per(i, n / 2, 1) chkmax(ans[i], ans[i + 1]);
  rep(i, 1, n) {
    printf("%d\n", i & 1 ? 1 : ans[i >> 1]);
  }
}

}

namespace task2 {

const int M = N * 20;
const int INF = 1e8;
int rt[N], id, ls[M], rs[M], mx[M], tag[M];
int n2, ans[N], sz[N], d[N], f[N][20];
void down(int u) {
  if(tag[u] == -INF) return ;
  if(ls[u]) chkmax(tag[ls[u]], tag[u]);
  if(rs[u]) chkmax(tag[rs[u]], tag[u]);
}
void insert(int &u, int l, int r, int p, int v) {
  if(!u) { u = ++ id; mx[u] = v; tag[u] = -INF; }
  else {
    if(l == r) {
      chkmax(ans[l], mx[u] + tag[u]);
      tag[u] = -INF;
      chkmax(mx[u], v);
    } else {
      down(u); tag[u] = -INF; chkmax(mx[u], v);
    }
  }
  if(l == r) return ;
  int mid = (l + r) >> 1;
  if(p <= mid) insert(ls[u], l, mid, p, v);
  else insert(rs[u], mid + 1, r, p, v);
}
void dfs(int u, int fa = 0) {
  sz[u] = 1; d[u] = d[fa] + 1; f[u][0] = fa;
  rep(i, 1, 19) if(!(f[u][i] = f[f[u][i - 1]][i - 1])) break ;
  for(int v : G[u]) if(v ^ fa) {
    dfs(v, u); sz[u] += sz[v];
  }
}
int curd;
int merge(int u, int v, int l, int r) {
  if(!u || !v) return u | v;
  if(l == r) {
    chkmax(ans[l], max(mx[u] + tag[u], mx[v] + tag[v]));
    chkmax(ans[l], mx[u] + mx[v] - curd);
    chkmax(mx[u], mx[v]);
    tag[u] = -INF;
    return u;
  }
  down(u); down(v); tag[u] = -INF;
  if(ls[u] && rs[v]) chkmax(tag[ls[u]], mx[rs[v]] - curd);
  if(rs[u] && ls[v]) chkmax(tag[ls[v]], mx[rs[u]] - curd);
  chkmax(mx[u], mx[v]);
  int mid = (l + r) >> 1;
  ls[u] = merge(ls[u], ls[v], l, mid);
  rs[u] = merge(rs[u], rs[v], mid + 1, r);
  return u;
}
int query(int u, int l, int r, int ql, int qr) {
  if(!u) return 0;
  if(l == ql && r == qr) return mx[u];
  int mid = (l + r) >> 1;
  if(qr <= mid) return query(ls[u], l, mid, ql, qr);
  if(ql > mid) return query(rs[u], mid + 1, r, ql, qr);
  return max(query(ls[u], l, mid, ql, mid), query(rs[u], mid + 1, r, mid + 1, qr));
}
void work(int u, int l, int r) {
  if(!u) return ;
  if(l == r) {
    chkmax(ans[l], mx[u] + tag[u]);
    return ;
  }
  down(u);
  int mid = (l + r) >> 1;
  work(ls[u], l, mid);
  work(rs[u], mid + 1, r);
}
void dfs2(int u, int fa = 0) {
  for(int v : G[u]) if(v ^ fa) {
    dfs2(v, u);
    curd = 2 * d[u] - 1;
    rt[u] = merge(rt[u], rt[v], 1, n);
  }
  insert(rt[u], 1, n, sz[u], d[u]);
  if(u > 1 && n - sz[u] <= n2) {
    chkmax(ans[n - sz[u]], query(rt[u], 1, n, n - sz[u], n) - d[u] + 2);
  }
}
void solve(int u) {
  if(sz[u] > n2) return ;
  int v = u;
  for(int i = 19; ~i; i --) if(f[v][i] && n - sz[f[v][i]] >= sz[u]) {
    v = f[v][i];
  }
  chkmax(ans[sz[u]], d[u] - d[v] + 2);
}
void main() {
  n2 = n >> 1;
  dfs(1); dfs2(1); work(rt[1], 1, n);
  rep(i, 2, n) solve(i);
  ans[n2 + 1] = 1;
  per(i, n2, 1) chkmax(ans[i], ans[i + 1]);
  rep(i, 1, n) {
    printf("%d\n", i & 1 ? 1 : ans[i >> 1]);
  }
}

}
int main() {
  scanf("%d", &n);
  int u, v;
  rep(i, 1, n - 1) {
    scanf("%d%d", &u, &v);
    G[u].pb(v); G[v].pb(u);
  }
  if(n <= 4000) {
    task1::main();
  } else {
    task2::main();
  }
  return 0;
}