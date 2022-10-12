#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e5 + 10, M = 35 * N;
int n, q, id, a[N], extra[N], ls[M], rs[M], sz[M], l[N * 5], r[N * 5], k[N * 5], T[N], c[N];
ll sum[M], ans[N * 5], s[N];
vector<int> vec[N];
void update(int p, int &u, int l, int r, int x) {
   u = ++ id; sum[u] = sum[p] + x; sz[u] = sz[p] + 1;
   if(l == r) { ls[u] = rs[u] = 0; return ; }
   int mid = (l + r) >> 1;
   if(x <= mid) rs[u] = rs[p], update(ls[p], ls[u], l, mid, x);
   else ls[u] = ls[p], update(rs[p], rs[u], mid + 1, r, x);
}
ll query(int u, int v, int l, int r, int k) {
   if(l == r) return (ll) k * l;
   int mid = (l + r) >> 1, t = sz[rs[u]] - sz[rs[v]];
   if(t >= k) return query(rs[u], rs[v], mid + 1, r, k);
   return sum[rs[u]] - sum[rs[v]] + query(ls[u], ls[v], l, mid, k - t);
}
int main() {
   scanf("%d%d", &n, &q);
   rep(i, 1, n) { scanf("%d", a + i); s[i] = s[i - 1] + a[i]; }
   rep(i, 1, q) { scanf("%d%d%d", l + i, r + i, k + i); ans[i] = s[r[i]] - s[l[i] - 1]; }
   rep(i, 1, n) {
      for(int x = a[i]; x >= 1; x >>= 1) {
         if(x - (x >> 1) == 1 && vec[i].size() && * -- vec[i].end() == 1) {
            extra[i] = 1;
         }
         vec[i].push_back(x - (x >> 1));
      }
   }
   rep(i, 1, n) extra[i] += extra[i - 1];
   for(int R = 1 << 30; R >= 1; R >>= 1) {
      int L = (R >> 1) + 1; id = 0;
      rep(i, 1, n) {
         int w = 0;
         for(int v : vec[i]) if(L <= v && v <= R) { w = v; break ; }
         if(w) update(T[i - 1], T[i], L, R, w); else T[i] = T[i - 1];
         s[i] = s[i - 1] + w; c[i] = c[i - 1] + (w > 0);
      }
      rep(i, 1, q) if(k[i]) {
         if(k[i] >= c[r[i]] - c[l[i] - 1]) {
            k[i] -= c[r[i]] - c[l[i] - 1];
            ans[i] -= s[r[i]] - s[l[i] - 1];
         } else {
            ans[i] -= query(T[r[i]], T[l[i] - 1], L, R, k[i]);
            k[i] = 0;
         }
      }
   }
   rep(i, 1, q) ans[i] -= min(k[i], extra[r[i]] - extra[l[i] - 1]);
   rep(i, 1, q) printf("%lld\n", ans[i]);
   return 0;   
}