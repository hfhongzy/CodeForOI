// #include <swap.h>
#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 2e5 + 10;
struct edge {
  int w, u, v;
};
bool mark[N];
int lgn, f[N], w[N], fa[20][N], d[N];
int find(int u) {
  return u == f[u] ? u : f[u] = find(f[u]);
}
void init(int n, int m, vector<int> vu, vector<int> vv, vector<int> vw) {
  vector<edge> e;
  rep(i, 0, m - 1) e.pb({vw[i], vu[i] + 1, vv[i] + 1});
  sort(e.begin(), e.end(), [&](edge x, edge y) { return x.w < y.w; });
  rep(i, 1, 2 * n - 1) f[i] = i;
  int c = n;
  rep(i, 0, m - 1) {
    int u = e[i].u, v = e[i].v; d[u] ++; d[v] ++;
    int x = find(u), y = find(v);
    if(x == y) {
      if(!mark[x]) {
        mark[x] = 1; w[x] = e[i].w;
      }
    } else {
      c ++; w[c] = e[i].w; mark[c] = mark[x] | mark[y]; f[x] = f[y] = c;
      fa[0][x] = fa[0][y] = c;
      if(!mark[c]) {
        mark[c] |= d[u] > 2 || d[v] > 2;
      }
    }
  }
  per(i, 2 * n - 1, 1) d[i] = d[fa[0][i]] + 1;
  for(lgn = 1; (1 << lgn) < 2 * n; lgn ++);
  lgn --;
  for(int i = 1; i <= lgn; i ++)
    rep(j, 1, 2 * n - 1) fa[i][j] = fa[i - 1][fa[i - 1][j]];
}
int getMinimumFuelCapacity(int u, int v) {
  u ++; v ++;
  if(d[u] < d[v]) swap(u, v);
  int c = d[u] - d[v];
  per(i, lgn, 0) if(c >> i & 1) u = fa[i][u];
  per(i, lgn, 0) if(fa[i][u] ^ fa[i][v]) {
    u = fa[i][u]; v = fa[i][v];
  }
  per(i, lgn, 0) if(fa[i][u] && !mark[fa[i][u]]) u = fa[i][u];
  u = fa[0][u];
  return mark[u] ? w[u] : -1;
}
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  vector<int> vu(m), vv(m), vw(m);
  rep(i, 0, m - 1) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    vu[i] = u; vv[i] = v; vw[i] = w;
  }
  init(n, m, vu, vv, vw);
  int q; scanf("%d", &q);
  rep(i, 0, q - 1) {
    int u, v;
    scanf("%d%d", &u, &v);
    printf("%d\n", getMinimumFuelCapacity(u, v));
  }
  return 0;
}