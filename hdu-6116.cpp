#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;
typedef long long ll;
const int N = 4096 + 10, mod = 998244353, _g = 3;
int qpow(int a, int b) {
  int ans = 1;
  for(; b >= 1; b >>= 1, a = (ll) a * a % mod)
    if(b & 1) ans = (ll) ans * a % mod;
  return ans;
}
int rev[N], len, w[N], inv_w[N];
void InitNTT(int n) {
  int k = 0;
  for(len = 1; len <= n; len <<= 1) k ++;
  for(int i = 1; i < len; i ++)
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
  w[0] = inv_w[0] = 1;
  int v = qpow(_g, (mod - 1) / len);
  for(int i = 1; i < len; i ++)
    inv_w[len - i] = w[i] = 1ll * w[i - 1] * v % mod;
}
void NTT(int *a, const int *w) {
  for(int i = 1; i < len; i ++)
    if(i < rev[i]) swap(a[i], a[rev[i]]);
  for(int i = 1; i < len; i <<= 1) {
    for(int j = 0, t = len / (i << 1); j < len; j += i << 1) {
      const int *wn = w;
      for(int k = j; k < j + i; k ++, wn += t) {
        int t1 = a[k], t2 = 1ll * *wn * a[k + i] % mod;
        a[k] = (t1 + t2) % mod; a[k + i] = (t1 - t2 + mod) % mod;
      }
    }
  }
  if(w == inv_w) {
    int v = mod - (mod - 1) / len;
    for(int i = 0; i < len; i ++)
      a[i] = 1ll * a[i] * v % mod;
  }
}
int fac[N], fav[N];
int n, a, b, c, d, A[N], B[N], C[N], D[N];
int Co(int n, int m) {
  return n < m ? 0 : 1ll * fac[n] * fav[m] % mod * fav[n - m] % mod;
}
int _pw(int n) { return n & 1 ? mod - 1 : 1; }
int main() {
  fac[0] = 1;
  for(int i = 1; i < N; i ++) fac[i] = (ll) fac[i - 1] * i % mod;
  fav[N - 1] = qpow(fac[N - 1], mod - 2);
  for(int i = N - 1; i >= 1; i --) fav[i - 1] = (ll) fav[i] * i % mod;
  while(~ scanf("%d%d%d%d", &a, &b, &c, &d)) {
    n = a + b + c + d; InitNTT(n);
    A[0] = B[0] = C[0] = D[0] = 0;
    for(int i = 1; i <= a; i ++) A[i] = 1ll * Co(a - 1, i - 1) * fav[i] % mod;
    for(int i = 1; i <= b; i ++) B[i] = 1ll * Co(b - 1, i - 1) * fav[i] % mod;
    for(int i = 1; i <= c; i ++) C[i] = 1ll * Co(c - 1, i - 1) * fav[i] % mod;
    for(int i = 1; i <= d; i ++) D[i] = 1ll * Co(d - 1, i - 1) * fav[i] % mod;
    for(int i = a + 1; i <= len; i ++) A[i] = 0;
    for(int i = b + 1; i <= len; i ++) B[i] = 0;
    for(int i = c + 1; i <= len; i ++) C[i] = 0;
    for(int i = d + 1; i <= len; i ++) D[i] = 0;
    NTT(A, w); NTT(B, w); NTT(C, w); NTT(D, w);
    for(int i = 0; i < len; i ++) A[i] = 1ll * A[i] * B[i] % mod * C[i] % mod * D[i] % mod;
    NTT(A, inv_w);
    int ans = 0;
    for(int i = 0; i < n; i ++) {
      (ans += 1ll * _pw(i) * A[n - i] % mod * fac[n - i] % mod) %= mod;
    }
    printf("%d\n", ans);
  }
  return 0;
}
