#include <algorithm>
#include <cstdio>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int M = 2e5 + 10, N = 2e5*20 + 10;
int n, m, id, rt[M], ls[N], rs[N], fa[N], d[N];
void build(int &u, int l, int r) {
   u = ++ id;
   if(l == r) { fa[u] = l; d[u] = 1; return ; }
   int mid = (l + r) >> 1;
   build(ls[u], l, mid);
   build(rs[u], mid + 1, r);
}
void update(int p, int &u, int l, int r, int x, int y, int *arr) {
   int P = p; u = ++ id;
   if(l == r) {
      if(arr != fa) fa[u] = fa[P];
      if(arr != d) d[u] = d[P];
      arr[u] = y;
      return ;
   }
   int mid = (l + r) >> 1;
   if(x <= mid) rs[u] = rs[P], update(ls[P], ls[u], l, mid, x, y, arr);
   else ls[u] = ls[P], update(rs[P], rs[u], mid + 1, r, x, y, arr);
}
int query(int u, int l, int r, int qx) {
   if(l == r) return u;
   int mid = (l + r) >> 1;
   if(qx <= mid) return query(ls[u], l, mid, qx);
   return query(rs[u], mid + 1, r, qx);
}
int find(int rt, int u) {
   int x = query(rt, 1, n, u);
   return fa[x] == u ? x : find(rt, fa[x]);
}
void merge(int &nw, int rt, int u, int v) {
   int x = find(rt, u), y = find(rt, v);
   if(x == y) { nw = rt; return ; }
   if(d[x] > d[y]) swap(x, y);
   update(rt, nw, 1, n, fa[x], fa[y], fa);
   if(d[x] + 1 > d[y]) update(nw, nw, 1, n, fa[y], d[x] + 1, d);
}
int main() {
   scanf("%d%d", &n, &m); build(rt[0], 1, n);
   rep(i, 1, m) {
      int op, u, v;
      scanf("%d%d", &op, &u);
      if(op == 1) {
         scanf("%d", &v);
         merge(rt[i], rt[i - 1], u, v);
      }
      if(op == 2) { rt[i] = rt[u]; }
      if(op == 3) {
         scanf("%d", &v); rt[i] = rt[i - 1];
         printf("%d\n", (int) (find(rt[i], u) == find(rt[i], v)));
      }
   }
   return 0;
}