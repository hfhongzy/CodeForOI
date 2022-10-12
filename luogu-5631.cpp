#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 2e6 + 10;
struct Edge {
  int u, v, w;
} e[N];
int n, m, p[N];
struct ufs {
  int f[N], sz[N];
  void init() {
    rep(i, 1, n) sz[i] = 1, f[i] = i;
  }
  int find(int u) {
    while(u != f[u]) u = f[u];
    return u;
  }
  int st[N][2], top;
  void unite(int u, int v) {
    u = find(u); v = find(v);
    if(u == v) return ;
    if(sz[u] > sz[v]) swap(u, v);
    f[u] = v; sz[v] += sz[u];
    ++ top; st[top][0] = v; st[top][1] = u;
  }
  void pop() {
    int v = st[top][0], u = st[top][1];
    sz[v] -= sz[u]; f[u] = u; top --;
  }
} T;
void solve(int l, int r) {
  if(l == r) {
    if(T.sz[T.find(1)] == n) {
      printf("%d\n", l);
      exit(0);
    }
    return ;
  }
  int mid = (l + r) >> 1;
  int t = T.top;
  rep(i, mid + 1, r) {
    rep(j, (i ? p[i - 1] + 1 : 0), p[i])
      T.unite(e[j].u, e[j].v);
  }
  solve(l, mid);
  while(T.top != t) T.pop();
  rep(i, l, mid) {
    rep(j, (i ? p[i - 1] + 1 : 1), p[i])
      T.unite(e[j].u, e[j].v);
  }
  solve(mid + 1, r);
  while(T.top != t) T.pop();
}
int main() {
  scanf("%d%d", &n, &m);
  int u, v, w, z = 0;
  rep(i, 1, m) {
    scanf("%d%d%d", &u, &v, &w);
    e[i] = {u, v, w};
    z = max(z, w);
  }
  sort(e + 1, e + m + 1, [&](Edge l, Edge r) {
    return l.w < r.w;
  });
  int cur = 0;
  rep(i, 0, z) {
    while(cur < m && e[cur + 1].w <= i) ++ cur;
    p[i] = cur;
  }
  T.init();
  solve(0, z);
  return 0;
}