#include <algorithm>
#include <cstdio>
#include <vector>
#include <map>
#define pb push_back
#define pii pair<int, int>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 210, M = 1e4 + 10;
int n, q, c1[M], a[N][N];
int ID(int x, int y) { return (x - 1) * n + y; }
struct Main {

vector<int> edges;
map<pii, int> Map;
vector<pii> seg[M << 2];
void modify(int u, int l, int r, int ql, int qr, pii e) {
   if(l == ql && r == qr) { seg[u].pb(e); return ; }
   int mid = (l + r) >> 1;
   if(qr <= mid) modify(u << 1, l, mid, ql, qr, e);
   else if(ql > mid) modify(u << 1 | 1, mid + 1, r, ql, qr, e);
   else {
      modify(u << 1, l, mid, ql, mid, e);
      modify(u << 1 | 1, mid + 1, r, mid + 1, qr, e);
   }
}
void push(int x, int y, int t) {
   if(x > y) swap(x, y); 
   edges.pb(t); Map[pii(x, y)] = (int) edges.size() - 1;
}
void pop(int x, int y, int t2) {
   if(x > y) swap(x, y);
   int e = Map[pii(x, y)];
   modify(1, 1, q + 1, edges[e], t2, pii(x, y));
   edges[e] = -1;
}
int f[N * N], sz[N * N], ans[M], bcc, top, st[N * N * 2];
int find(int u) { return f[u] == u ? u : find(f[u]); }
void merge(int u, int v) {
   u = find(u); v = find(v);
   if(u != v) {
      if(sz[u] > sz[v]) swap(u, v);
      f[u] = v; sz[v] += sz[u]; st[++ top] = u; bcc --;
   }
}
void stpop() {
   int u = st[top --]; sz[f[u]] -= sz[u]; f[u] = u; bcc ++;
}
void solve(int u, int l, int r) {
   int cur = top;
   rep(i, 0, (int) seg[u].size() - 1) {
      merge(seg[u][i].first, seg[u][i].second);
   }
   if(l == r) {
      ans[l] = bcc;
   } else {
      int mid = (l + r) >> 1;
      solve(u << 1, l, mid);
      solve(u << 1 | 1, mid + 1, r);
   }
   while(top > cur) stpop();
}

} T[2];
int main() {
   scanf("%d", &n);
   rep(i, 1, n) rep(j, 1, n) {
      int &c = a[i][j];
      scanf("%d", &c); c1[1] += c;
      if(i > 1 && a[i - 1][j] == c) T[c].push(ID(i - 1, j), ID(i, j), 1);
      if(j > 1 && a[i][j - 1] == c) T[c].push(ID(i, j - 1), ID(i, j), 1);
   }
   const int dx[] = {1, 0, -1, 0};
   const int dy[] = {0, 1, 0, -1};
   scanf("%d", &q);
   rep(i, 2, q + 1) {
      int u, v; scanf("%d%d", &u, &v);
      c1[i] = c1[i - 1] + (a[u][v] ? -1 : 1);
      for(int d = 0; d < 4; d ++) {
         int x = u + dx[d], y = v + dy[d];
         if(1 <= min(x, y) && max(x, y) <= n) {
            if(a[u][v] == a[x][y]) {
               T[a[u][v]].pop(ID(u, v), ID(x, y), i - 1);
            } else {
               T[a[x][y]].push(ID(u, v), ID(x, y), i);
            }
         }
      }
      a[u][v] ^= 1;
   }
   rep(i, 1, n) rep(j, 1, n) {
      int &c = a[i][j];
      if(i > 1 && a[i - 1][j] == c) T[c].pop(ID(i - 1, j), ID(i, j), q + 1);
      if(j > 1 && a[i][j - 1] == c) T[c].pop(ID(i, j - 1), ID(i, j), q + 1);
   }
   rep(i, 1, n * n) T[0].f[i] = T[1].f[i] = i, T[0].sz[i] = T[1].sz[i] = 1;
   T[0].bcc = T[1].bcc = n * n;
   T[0].solve(1, 1, q + 1); T[1].solve(1, 1, q + 1);
   rep(i, 2, q + 1) {
      printf("%d %d\n", T[1].ans[i] - (n * n - c1[i]), T[0].ans[i] - c1[i]);
   }
   return 0;
}