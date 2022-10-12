#include <algorithm>
#include <cstring>
#include <vector>
#include <cstdio>
using namespace std;
typedef long long ll;
const int N = 8e5 + 10, mod = 998244353;
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
  int v = qpow(3, (mod - 1) / len);
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
int n, k, S[N], fav[N];
void stirling(int m) {
  static int A[N], B[N];
  int t = 1;
  for(int i = 1; i <= m; i ++) t = 1ll * t * i % mod;
  fav[m] = qpow(t, mod - 2);
  for(int i = m; i >= 1; i --) fav[i - 1] = 1ll * fav[i] * i % mod;
  for(int i = 0; i <= m; i ++) A[i] = (i & 1 ? mod - 1ll : 1ll) * fav[i] % mod;
  for(int i = 0; i <= m; i ++) B[i] = 1ll * qpow(i, m) * fav[i] % mod;     
  InitNTT(2 * m); NTT(A, w); NTT(B, w);
  for(int i = 0; i < len; i ++) A[i] = 1ll * A[i] * B[i] % mod;
  NTT(A, inv_w);
  for(int i = 0; i <= m; i ++) S[i] = A[i];
}
int solve(int n) {
  stirling(k);
  int t = 1, t2 = qpow(2, n), ans = 0;
  for(int i = 0; i <= k; i ++) {
    (ans += 1ll * t * t2 % mod * S[i] % mod) %= mod;
    t = 1ll * t * (n - i) % mod;
    t2 = 1ll * t2 * ((mod + 1) >> 1) % mod;
  }
  return ans;
}
int main() {
  scanf("%d%d", &n, &k);
  int ans = 1ll * n * qpow(2, (n - 1ll) * (n - 2) / 2 % (mod - 1)) % mod * solve(n - 1) % mod;
  printf("%d\n", ans);
  return 0;
}
