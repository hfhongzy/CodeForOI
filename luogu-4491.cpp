#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 1e7 + 10, M = 1e5 + 10, mod = 1004535809;
int n, m, s, w[M], fac[N], fav[N], f[M], g[M];
int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = 1ll * a * a % mod)
      if(b & 1) ans = 1ll * ans * a % mod;
   return ans;
}
void init(int n) {
   fac[0] = 1;
   for(int i = 1; i <= n; i ++) fac[i] = 1ll * fac[i - 1] * i % mod;
   fav[n] = qpow(fac[n], mod - 2);
   for(int i = n; i >= 1; i --) fav[i - 1] = 1ll * fav[i] * i % mod;
}
int C(int n, int m) {
   return 1ll * fac[n] * fav[m] % mod * fav[n - m] % mod;
}
int len, rev[M * 4], A[M * 4], B[M * 4], W[M * 4], iW[M * 4];
void InitNTT(int n) {
   int k = 0;
   for(len = 1; len <= n; len <<= 1) k ++;
   for(int i = 1; i < len; i ++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
   W[0] = iW[0] = 1; int omega = qpow(3, (mod - 1) / len);
   for(int i = 1; i < len; i ++) W[i] = iW[len - i] = 1ll * W[i - 1] * omega % mod;
}
void NTT(int *a, const int *w) {
   for(int i = 1; i < len; i ++)
      if(i < rev[i]) swap(a[i], a[rev[i]]);
   for(int i = 1; i < len; i <<= 1) {
      for(int t = len / (i << 1), j = 0; j < len; j += i << 1) {
         const int *wn = w;
         for(int k = j; k < j + i; k ++, wn += t) {
            int p = a[k], q = 1ll * *wn * a[k + i] % mod;
            a[k] = (p + q) % mod; a[k + i] = (p - q + mod) % mod;
         }
      }
   }
   if(w == iW) {
      int v = mod - (mod - 1) / len;
      for(int i = 0; i < len; i ++)
         a[i] = 1ll * a[i] * v % mod;
   }
}
int main() {
   scanf("%d%d%d", &n, &m, &s);
   for(int i = 0; i <= m; i ++) scanf("%d", w + i);
   init(max(s, max(n, m)));
   // init(10000);
   int ss = 1, l = min(m, n / s);
   for(int i = 0; i <= l; i ++) {
      f[i] = 1ll * C(m, i) * fac[n] % mod * fav[n - i * s] % mod * ss % mod * qpow(m - i, n - i * s) % mod;
      ss = 1ll * ss * fav[s] % mod;
   }
   // int res = 0;
   // for(int i = 0; i <= l; i ++) {
   //    for(int j = i; j <= l; j ++) {
   //       (g[i] += ( (j - i) & 1 ? mod - 1ll : 1ll ) * C(j, i) % mod * f[j] % mod) %= mod;
   //    }
   //    (res += 1ll * g[i] * w[i] % mod) %= mod;
   // }
   for(int i = 0; i <= l; i ++) A[i] = 1ll * fac[i] * f[i] % mod;
   for(int i = 0; i <= l; i ++) B[l - i] = (i & 1 ? mod - 1ll : 1ll) * fav[i] % mod;
   InitNTT(2 * l); NTT(A, W); NTT(B, W);
   for(int i = 0; i < len; i ++) A[i] = 1ll * A[i] * B[i] % mod;
   NTT(A, iW);
   int res = 0;
   for(int i = 0; i <= l; i ++) (res += 1ll * A[i + l] * w[i] % mod * fav[i] % mod) %= mod;
   printf("%d\n", res);
   return 0;
}