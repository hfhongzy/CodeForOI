#include <algorithm>
#include <cstdio>
#include <cmath>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
typedef double db;
using namespace std;
const int N = 310, base = 2333, mod = 998244853;
int n, m, pw[N];
char s[N][N];
db a[N][N], bin[N];
struct tool {
   int val[N];
   void build(char *s) {
      val[0] = 0;
      rep(i, 1, m) {
         val[i] = (1ll * val[i - 1] * base + s[i]) % mod; 
      }
   }
   int query(int l, int r) {
      return (val[r] - 1ll * val[l - 1] * pw[r - l + 1] % mod + mod) % mod;
   }
} h[N];
void init() {
   pw[0] = 1;
   rep(i, 1, m) pw[i] = 1ll * pw[i - 1] * base % mod;
   bin[0] = 1;
   rep(i, 1, m) bin[i] = bin[i - 1] * 2;
}
void gauss(int n) {
   rep(i, 1, n) {
      int j = i;
      rep(k, i, n) if(fabs(a[k][i]) > fabs(a[j][i])) j = k;
      if(j != i) rep(k, i, n + 1) swap(a[j][k], a[i][k]);
      rep(j, i + 1, n) {
         db t = a[j][i] / a[i][i];
         rep(k, i, n + 1) a[j][k] -= t * a[i][k];
      }
   }
   per(i, n, 1) {
      rep(j, i + 1, n) a[i][n + 1] -= a[i][j] * a[j][n + 1];
      a[i][n + 1] /= a[i][i];
   }
}
int main() {
   scanf("%d%d", &n, &m); init();
   rep(i, 1, n) {
      scanf("%s", s[i] + 1);
      h[i].build(s[i]);
   }
   rep(i, 1, n) a[i][n + 1] = -1;
   rep(i, 1, n) rep(j, 1, n) rep(k, 1, m)
      if(h[i].query(1, k) == h[j].query(m - k + 1, m)) {
         a[i][j] += bin[k];
      }
   rep(i, 1, n) a[n + 1][i] = 1;
   a[n + 1][n + 2] = 1;
   gauss(n + 1);
   rep(i, 1, n) printf("%.8f\n", a[i][n + 2]);
   return 0;
}