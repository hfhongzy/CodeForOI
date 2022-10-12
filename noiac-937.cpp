#include <algorithm>
#include <cstdio>
#include <vector>
#define rep(i, j, k) for(int i = j, _k = k; i <= _k; ++ i)
#define per(i, j, k) for(int i = j, _k = k; i >= _k; -- i)
#define fs first
#define sc second
using namespace std;
typedef pair<int, int> P;
const int N = 1e5 + 10, M = 2e6 + 10;
int n, q, logn, a[N], ans[N], d[N], idx, f[N][20], id[N][20];
vector<int> G[N];
P b[M];
int Max(int x, int y) {
   b[++ idx] = (!x || !y) ? P(x | y, x | y) : P(x, y);
   return idx;
}
void dfs(int u, int fa = 0) {
   f[u][0] = fa; id[u][0] = u; d[u] = d[fa] + 1;
   rep(i, 1, logn - 1) {
      f[u][i] = f[f[u][i - 1]][i - 1];
      if(!f[u][i]) break ;
      id[u][i] = Max(id[u][i - 1], id[f[u][i - 1]][i - 1]);
   }
   rep(i, 0, (int) G[u].size() - 1) {
      int v = G[u][i];
      if(v != fa) {
         dfs(v, u);
      }
   }
}
int query(int u, int v) {
   if(d[u] < d[v]) swap(u, v);
   int c = d[u] - d[v], la = 0;
   per(i, logn - 1, 0) if(c >> i & 1) {
      la = Max(id[u][i], la); u = f[u][i];
   }
   if(u != v) {
      per(i, logn - 1, 0) if(f[u][i] != f[v][i]) {
         la = Max(la, id[u][i]); la = Max(la, id[v][i]);
         u = f[u][i]; v = f[v][i];
      }
      la = Max(la, u); la = Max(la, v);
   }
   return Max(la, u == v ? u : f[u][0]);
}
int main() {
   scanf("%d%d", &n, &q);
   for(logn = 1; (1 << logn) <= n; logn ++) ;
   rep(i, 1, n - 1) {
      int u, v;
      scanf("%d%d", &u, &v);
      G[u].push_back(v);
      G[v].push_back(u);
   }
   idx = n; dfs(1);
   rep(i, 1, q) {
      int u, v;
      scanf("%d%d", &u, &v);
      ans[i] = query(u, v);
   }
   printf("%d\n", idx);
   rep(i, 1, idx - n) printf("%d %d\n", b[n + i].fs, b[n + i].sc);
   rep(i, 1, q) printf("%d\n", ans[i]);
   return 0;
}
/*
5 1
1 2
2 3
3 4
4 5
2 4
*/