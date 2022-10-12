#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;

const int N = 3010;
const int mod = 1e9 + 7;

int n, a[N], b[N], g[N][N], c[N], C[N][N], f[N][N], fac[N];

void ADD(int &x, int y) { (x += y) >= mod ? x -= mod : 0; }
void DEC(int &x, int y) { (x -= y) < 0 ? x += mod : 0; }
int add(int x, int y) { return x + y >= mod ? x + y - mod : x + y; }

int main() {
   scanf("%d", &n);
   fac[0] = 1;
   rep(i, 1, n) fac[i] = 1ll * fac[i - 1] * i % mod;
   rep(i, 0, n) {
      C[i][0] = 1;
      rep(j, 1, i) C[i][j] = add(C[i - 1][j], C[i - 1][j - 1]);
   }
   rep(i, 1, n) scanf("%d", a + i);
   rep(i, 1, n) scanf("%d", b + i);
   sort(a + 1, a + n + 1); sort(b + 1, b + n + 1);
   c[n + 1] = n + 1;
   per(i, n, 1) {
      c[i] = c[i + 1];
      while(c[i] > 1 && b[c[i] - 1] >= a[i]) {
         c[i] --;
      }
   }
   g[n + 1][0] = 1;
   per(i, n, 1) rep(j, 0, n - i) if(g[i + 1][j]) {
      if(- c[i] + 1 + i + j > 0)
         ADD(g[i][j], g[i + 1][j] * (mod - c[i] + 1ll + i + j) % mod);
      ADD(g[i][j + 1], g[i + 1][j]);
   }
   // printf("%d\n", g[1][0]);
   f[0][0] = 1;
   rep(i, 1, n) rep(j, 0, i - 1) if(f[i - 1][j]) {
      rep(k, 0, min(j, c[i + 1] - c[i])) {
         ll tmp = 1ll * f[i - 1][j] * C[j][k] % mod;
         ADD(f[i][j - k + 1], tmp * C[ c[i + 1] - c[i] ][k] % mod * fac[k] % mod);
         ADD(f[i][j - k], tmp * C[ c[i + 1] - c[i] ][k + 1] % mod * fac[k + 1] % mod);
      }
   }
   // cerr << "f[1][1] = " << f[1][1] << endl;
   int ans = g[1][0];
   rep(i, 1, n) {
      rep(j, 0, n - i) if(g[i + 1][j]) {
         int k = n - c[i] + 1 - (n - i - j);
         if(k >= 0) {
            // if(g[i + 1][j] * f[i - 1][k] > 0) {
            //    printf("i = %d (right not match %d, k = %d), %d & %d\n", i, j, k, f[i - 1][k], g[i + 1][j]);
            // }
            ans = (ans + (ll)g[i + 1][j] * f[i - 1][k] % mod * fac[k]) % mod;
         }
      }
   }

   printf("%d\n", ans);
   return 0;
}