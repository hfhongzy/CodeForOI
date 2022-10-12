#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

const int N = 5e5 + 10;

int n, m, a[N], bit[N];
void build(int *a) {
   rep(i, 1, n) bit[i] = a[i] - a[i & (i - 1)];
}
void add(int u, int v) {
   for(; u <= n; u += u & (-u)) {
      bit[u] += v;
   }
}
int qry(int u) {
   int ans = 0;
   for(; u >= 1; u &= u - 1) {
      ans += bit[u];
   }
   return ans;
}
int main() {
   int op, x, y, v;
   scanf("%d%d", &n, &m);
   rep(i, 1, n) scanf("%d", a + i);
   build(a);
   rep(i, 1, m) {
      scanf("%d%d", &op, &x);
      if(op == 1) {
         scanf("%d%d", &y, &v); add(x, v); add(y + 1, -v);
      }
      if(op == 2) {
         printf("%d\n", qry(x));
      }
   }
   return 0;
}