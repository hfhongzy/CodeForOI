#include <algorithm>
#include <cstdio>
#define rep(i, j, k) for(int i = j; i <= k; i ++)
#define per(i, j, k) for(int i = j; i >= k; i --)
using namespace std;
const int N = 1e5 + 10, T = N * 20;
int n, q, m, a[N], id;
int ls[T], rs[T], w[T], rt[N];
void build(int &u, int l, int r) {
   u = ++ id;
   if(l == r) { w[u] = -1; return ; }
   int mid = (l + r) >> 1;
   build(ls[u], l, mid); build(rs[u], mid + 1, r);
}
void update(int p, int &u, int l, int r, int pos, int val) {
   u = ++ id;
   if(l == r) { w[u] = val; return ; }
   int mid = (l + r) >> 1;
   if(pos <= mid) rs[u] = rs[p], update(ls[p], ls[u], l, mid, pos, val);
   else ls[u] = ls[p], update(rs[p], rs[u], mid + 1, r, pos, val);
}
int query(int u, int l, int r, int p) {
   if(l == r) return w[u];
   int mid = (l + r) >> 1;
   if(p <= mid) return query(ls[u], l, mid, p);
   return query(rs[u], mid + 1, r, p);
}
int main() {
   scanf("%*d%d%d%d", &n, &q, &m);
   rep(i, 1, n) scanf("%d", a + i);
   build(rt[n + 1], 1, m);
   per(i, n, 1) {
      update(rt[i + 1], rt[i], 1, m, a[i], i);
   }
   rep(i, 1, q) {
      static int s, seq[N];
      scanf("%d", &s);
      bool tag = 1;
      rep(j, 1, s) scanf("%d", seq + j);
      int cur = 0;
      rep(j, 1, s) {
         cur = cur == n ? -1 : query(rt[cur + 1], 1, m, seq[j]);
         if(cur == -1) { tag = 0; break ; }
      }
      puts(tag ? "Yes" : "No");
   }
   return 0;
}