#include <bits/stdc++.h>
#define pc __builtin_popcount
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int mod = 1e9 + 9;
void uadd(int &x, const int &y) { (x += y) >= mod ? x -= mod : 0; }
void udec(int &x, const int &y) { (x -= y) < 0 ? x += mod : 0; }
int n, x, a[21][1 << 21], b[21][1 << 21], c[21][1 << 21];
void fwt(int *a, int n) {
   for(int i = 1; i < n; i <<= 1) {
      for(int j = 0; j < n; j += i << 1) {
         for(int k = 0; k < i; k ++) {
            uadd(a[j + k + i], a[j + k]);
         }
      }
   }
}
void ifwt(int *a, int n) {
   for(int i = n / 2; i >= 1; i >>= 1) {
      for(int j = 0; j < n; j += i << 1) {
         for(int k = 0; k < i; k ++) {
            udec(a[j + k + i], a[j + k]);
         }
      }
   }
}
int main() {
   scanf("%d", &n);
   for(int i = 0; i < (1 << n); i ++) scanf("%d", &x), a[pc(i)][i] = x;
   for(int i = 0; i < (1 << n); i ++) scanf("%d", &x), b[pc(i)][i] = x;
   for(int i = 0; i <= n; i ++) fwt(a[i], 1 << n), fwt(b[i], 1 << n);
   for(int i = 0; i <= n; i ++)
      for(int j = 0; j <= n - i; j ++)
         for(int k = 0; k < (1 << n); k ++)
            c[i + j][k] = (c[i + j][k] + 1ll * a[i][k] * b[j][k]) % mod;
   for(int i = 0; i <= n; i ++) ifwt(c[i], 1 << n);
   for(int i = 0; i < (1 << n); i ++) printf("%d ", c[pc(i)][i]);
   return 0;
}