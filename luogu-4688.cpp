#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
struct query {
   int l, r, id;
} q[N];
int n, m, a[N], b[N], cnt[N], vis[N], len[N];
bitset<N> res, ans[N / 3 + 5];
void add(int x) {
   cnt[x] ++;
   res[x + cnt[x] - 1] = 1;
}
void del(int x) {
   res[x + cnt[x] - 1] = 0;
   cnt[x] --;
}
void solve(int m) {
   int sz = max(1, (int)(n / sqrt(m)));
   sort(q + 1, q + m + 1, [&](query x, query y) {
      return x.l / sz == y.l / sz ? x.r < y.r : x.l / sz < y.l / sz;
   });
   // for(int i = 1; i <= m; i ++) {
   //    printf("%d %d %d\n", q[i].l, q[i].r, q[i].id);
   // }
   int l = q[1].l, r = l - 1;
   for(int i = 1; i <= m / 3; i ++) vis[i] = 0;
   for(int i = 1; i <= n; i ++) cnt[i] = 0;
   res.reset();
   for(int i = 1; i <= m; i ++) {
      while(l > q[i].l) add(a[-- l]);
      while(r < q[i].r) add(a[++ r]);
      while(l < q[i].l) del(a[l ++]);
      while(r > q[i].r) del(a[r --]);
      if(vis[ q[i].id ]) {
         ans[ q[i].id ] &= res;
      } else {
         ans[ q[i].id ] = res;
      }
      vis[ q[i].id ] ++;
   }
   for(int i = 1; i <= m / 3; i ++) {
      printf("%d\n", len[i] - 3 * (int)ans[i].count());
   }
}
int main() {
   scanf("%d%d", &n, &m);
   for(int i = 1; i <= n; i ++) {
      scanf("%d", a + i); b[i] = a[i];
   }
   sort(b + 1, b + n + 1);
   for(int i = 1; i <= n; i ++) {
      a[i] = lower_bound(b + 1, b + n + 1, a[i]) - b;
   }
   int vv = 1e5 / 3, p = 0;
   for(int i = 1; i <= m; i ++) {
      p ++; scanf("%d%d", &q[p].l, &q[p].r);
      p ++; scanf("%d%d", &q[p].l, &q[p].r);
      p ++; scanf("%d%d", &q[p].l, &q[p].r);
      q[p].id = q[p - 1].id = q[p - 2].id = p / 3;
      len[p / 3] = q[p - 2].r - q[p - 2].l + q[p - 1].r - q[p - 1].l + q[p].r - q[p].l + 3;
      if(!-- vv || i == m) {
         solve(p); p = 0; vv = 1e5 / 3;
      }
   }
   return 0;
}