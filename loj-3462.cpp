#include <bits/stdc++.h>
#define debug(...) fprintf(stderr, __VA_ARGS__);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 3e5 + 10;
const int M = 32 * N;
struct pa {
  int x, y;
};
int n, m, k, id, rt[N], ls[M], rs[M], z[M], f[N];
int find(int u) { return u == f[u] ? u : f[u] = find(f[u]); }
queue<pa> q;
void insert(int &u, int l, int r, int w, int v) {
  if(!u) u = ++ id;
  if(l == r) {
    if(z[u]) {
      q.push({z[u], v});
    }
    z[u] = v;
    return ;
  }
  int mid = (l + r) >> 1;
  if(w <= mid) insert(ls[u], l, mid, w, v);
  else insert(rs[u], mid + 1, r, w, v);
}
int merge(int x, int y, int l, int r) {
  if(!x || !y) return x | y;
  if(l == r) {
    if(z[x] && z[y]) q.push({z[x], z[y]});
    z[x] = z[x] ? z[x] : z[y];
    return x;
  } 
  int mid = (l + r) >> 1;
  ls[x] = merge(ls[x], ls[y], l, mid);
  rs[x] = merge(rs[x], rs[y], mid + 1, r);
  return x;
}
void solve(int x, int y) {
  int u = find(x), v = find(y);
  if(u == v) return ;
  // printf("%d!", x);
  f[u] = v; rt[v] = merge(rt[u], rt[v], 1, k);
}
int main() {
  scanf("%d%d%d", &n, &m, &k);
  int u, v, w;
  rep(i, 1, n) f[i] = i;
  rep(i, 1, m) {
    scanf("%d%d%d", &u, &v, &w);
    insert(rt[v], 1, k, w, u);
  }
  while(q.size()) {
    pa k = q.front(); q.pop(); solve(k.x, k.y);
  }
  vector<int> sz(n + 1);
  ll ans = 0;
  rep(i, 1, n) sz[find(i)] ++;
  rep(i, 1, n) if(f[i] == i) ans += sz[i] * (sz[i] - 1ll) / 2;
  printf("%lld\n", ans);
  return 0;
}