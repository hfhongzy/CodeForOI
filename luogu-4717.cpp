#include <algorithm>
#include <cstdio>
using namespace std;
const int mod = 998244353, N = 1 << 17 | 5;
int n, m, a[N], b[N], A[N], B[N];
void fwtor(int *a) {
   for(int i = 1; i < m; i <<= 1)
      for(int j = 0; j < m; j += i << 1)
         for(int k = 0; k < i; k ++)
            (a[j + k + i] += a[j + k]) %= mod;
}
void Ifwtor(int *a) {
   for(int i = 1; i < m; i <<= 1)
      for(int j = 0; j < m; j += i << 1)
         for(int k = 0; k < i; k ++)
            (a[j + k + i] += mod - a[j + k]) %= mod;
}
void fwtand(int *a) {
   for(int i = 1; i < m; i <<= 1)
      for(int j = 0; j < m; j += i << 1)
         for(int k = 0; k < i; k ++)
            (a[j + k] += a[j + k + i]) %= mod;
}
void Ifwtand(int *a) {
   for(int i = 1; i < m; i <<= 1)
      for(int j = 0; j < m; j += i << 1)
         for(int k = 0; k < i; k ++)
            (a[j + k] += mod - a[j + k + i]) %= mod;
}
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
void solve(void (*fwt)(int *), void (*Ifwt)(int *)) {
   copy(a, a + m, A); copy(b, b + m, B);
   fwt(A); fwt(B);
   for(int i = 0; i < m; i ++) A[i] = 1ll * A[i] * B[i] % mod;
   Ifwt(A);
   for(int i = 0; i < m; i ++) printf("%d ", A[i]);
   putchar('\n');
}
int main() {
   scanf("%d", &n); m = 1 << n;
   for(int i = 0; i < m; i ++) scanf("%d", a + i);
   for(int i = 0; i < m; i ++) scanf("%d", b + i);
   solve(fwtor, Ifwtor); solve(fwtand, Ifwtand); solve(fwtxor, Ifwtxor);
   return 0;
}