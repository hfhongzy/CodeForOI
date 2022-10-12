#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
const int mod = 1e9 + 7;
void upd(int &x, int y) {
   (x += y) >= mod ? x -= mod : 0;
}
int n, q, op[N], l[N], r[N], bit[N], c[N];
void ins(int u, int v) {
   for(; u <= n; u += u & (-u)) {
      upd(bit[u], v);
   }
}
int qry(int u) {
   int ans = 0;
   for(; u >= 1; u &= u - 1) {
      upd(ans, bit[u]);
   }
   return ans;
}
int main() {
   scanf("%d%d", &n, &q);
   rep(i, 1, q) {
      scanf("%d%d%d", op + i, l + i, r + i);
   }
   per(i, q, 1) {
      int x = qry(i) + 1;
      if(op[i] == 1) {
         upd(c[l[i]], x);
         upd(c[r[i] + 1], mod - x);
      }
      if(op[i] == 2) {
         ins(l[i], x);
         ins(r[i] + 1, mod - x);
      }
   }
   rep(i, 1, n) upd(c[i], c[i - 1]);
   rep(i, 1, n) printf("%d%c", c[i], " \n"[i == n]);
   return 0;
}
