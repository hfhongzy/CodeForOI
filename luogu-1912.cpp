#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
typedef long double db;
const int N = 1e5 + 10;
char s[N][32];
int n, L0, p, w[N], g[N];
db f[N];
db fpow(db x, int b) {
   db res = 1;
   for(; b >= 1; b >>= 1, x *= x) if(b & 1) res *= x;
   return res;
}
db calc(int len) { return fpow(len, p); }
void solve(int u) {
   if(!u) return ;
   solve(g[u]);
   rep(i, g[u] + 1, u) printf("%s%c", s[i] + 1, " \n"[i == u]);
}
int sect(int u, int v) { //u < v, v better
   int l = v + 1, r = n, ans = n + 1;
   while(l <= r) {
      int mid = (l + r) >> 1;
      if(f[v] + calc(abs(w[mid] - w[v] - 1 - L0)) <= f[u] + calc(abs(w[mid] - w[u] - 1 - L0))) {
         r = (ans = mid) - 1;
      } else {
         l = mid + 1;
      }
   }
   return ans;
}
int main() {
   int test; scanf("%d", &test);
   while(test --) {
      scanf("%d%d%d", &n, &L0, &p);
      rep(i, 1, n) scanf("%s", s[i] + 1), w[i] = w[i - 1] + strlen(s[i] + 1) + 1;
      static int q[N], se[N];
      int ql = 0, qr = 0; q[qr ++] = f[0] = 0;
      rep(i, 1, n) {
         while(qr - ql > 1 && se[ql + 1] <= i) ql ++;
         g[i] = q[ql]; f[i] = f[g[i]] + calc(abs(w[i] - w[g[i]] - 1 - L0));
         while(qr - ql > 1 && se[qr - 1] >= sect(q[qr - 1], i)) qr --;
         q[qr ++] = i; se[qr - 1] = sect(q[qr - 2], i);
      }
      const ll Lim = 1e18;
      // cout << f[n] << endl;
      ll res = ll(f[n] + 0.5);
      if(f[n] > 1e18 || res > Lim) {
         puts("Too hard to arrange");
      } else {
         printf("%lld\n", res);
         solve(n);
      }
      rep(i, 1, 20) putchar('-');
      putchar('\n');
   }
   return 0;
}
