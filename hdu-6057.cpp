#include <algorithm>
#include <cstdio>
using namespace std;
const int mod = 998244353, base = 1526, N = 1 << 19 | 5;
int n, m, a[N], b[N], cnt[N], A[20][N], B[20][N], C[20][N];
void fwtxor(int *a) {
   for(int i = 1; i < m; i <<= 1)
      for(int j = 0; j < m; j += i << 1)
         for(int k = 0; k < i; k ++) {
            int p = a[j + k], q = a[j + k + i];
            a[j + k] = (p + q) % mod; a[j + k + i] = (p - q + mod) % mod;
         }
}
void Ifwtxor(int *a) {
   const long long inv2 = (mod + 1) >> 1;
   for(int i = 1; i < m; i <<= 1)
      for(int j = 0; j < m; j += i << 1)
         for(int k = 0; k < i; k ++) {
            int p = a[j + k], q = a[j + k + i];
            a[j + k] = (p + q) * inv2 % mod; a[j + k + i] = (p - q + mod) * inv2 % mod;
         }
}
int bin(int b) {
   if(b <= 62) return (1ll << b) % mod;
   int x = bin(b >> 1); x = 1ll * x * x % mod;
   if(b & 1) x = (x + x) % mod; 
   return x;
}
int main() {
   // for(int i = 0; i < 10; i ++) printf("%d ", bin(i));
   scanf("%d", &n); m = 1 << n;
   for(int i = 1; i < m; i ++) cnt[i] = cnt[i & (i - 1)] + 1;
   for(int i = 0; i < m; i ++) scanf("%d", a + i), A[cnt[i]][i] = 1ll * a[i] * bin(cnt[i]) % mod;
   for(int i = 0; i < m; i ++) scanf("%d", b + i), B[cnt[i]][i] = b[i];
   for(int i = 0; i <= n; i ++) fwtxor(A[i]), fwtxor(B[i]);
   for(int j = 0; j <= n; j ++)
      for(int i = 0; i <= j; i ++)
         for(int k = 0; k < m; k ++)
            (C[j - i][k] += 1ll * A[i][k] * B[j][k] % mod) %= mod;
   for(int i = 0; i <= n; i ++) Ifwtxor(C[i]);
   int ans = 0, pw = 1;
   for(int i = 0; i < m; i ++, pw = 1ll * pw * base % mod)
      (ans += 1ll * pw * C[cnt[i]][i] % mod) %= mod;
   printf("%d\n", ans);
   return 0;
}