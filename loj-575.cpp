#include <algorithm>
#include <cstring>
#include <cstdio>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 4e5 + 10, mod = 998244353;
int len, rev[N], W[N], iW[N], fac[N], fav[N];
int qpow(int a, int b) {
  int ans = 1;
  for(; b >= 1; b >>= 1, a = 1ll * a * a % mod)
    if(b & 1) ans = 1ll * ans * a % mod;
  return ans;
}
inline int add(int x, int y) { return x + y >= mod ? x + y - mod : x + y; }
inline int dec(int x, int y) { return x - y < 0 ? x - y + mod : x - y; }
inline void upd(int &x, int y) { (x += y) >= mod ? x -= mod : 0; }
void InitNTT(int n) {
  len = 1; int k = 0;
  while(len <= n) len <<= 1, k ++;
  rep(i, 1, len - 1) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
  int w0 = qpow(3, (mod - 1) / len); W[0] = iW[len] = 1;
  rep(i, 1, len) W[i] = iW[len - i] = 1ll * W[i - 1] * w0 % mod;
}
void NTT(int *a, const int *W) {
  rep(i, 1, len - 1) if(i < rev[i]) swap(a[i], a[rev[i]]);
  for(int i = 1; i < len; i <<= 1) {
    for(int j = 0, t = len / (i << 1); j < len; j += i << 1) {
      const int *wn = W;
      for(int k = 0; k < i; k ++, wn += t) {
        int p = a[j + k], q = 1ll * *wn * a[j + k + i] % mod;
        a[j + k] = add(p, q); a[j + k + i] = dec(p, q);
      }
    }
  }
  if(W == iW) {
    int inv = mod - (mod - 1) / len;
    rep(i, 0, len - 1) a[i] = 1ll * a[i] * inv % mod;
  }
}
int n, f[N], c[N], A[N], B[N];
char s[N];
void solve(int l, int r) {
  if(l == r) {
    if(l == 0) f[0] = 1;
    else if(c[l - 1] & 1) f[l] = mod - f[l];
    return ;
  }
  int mid = (l + r) >> 1;
  solve(l, mid); InitNTT(mid - l + r - l);
  rep(i, 0, len - 1) A[i] = i <= mid - l && s[l + i] != '<' ? (c[l + i] & 1 ? mod - f[l + i] : f[l + i]) : 0;
  rep(i, 0, len - 1) B[i] = i <= r - l ? fav[i] : 0;
  NTT(A, W); NTT(B, W);
  rep(i, 0, len - 1) A[i] = 1ll * A[i] * B[i] % mod;
  NTT(A, iW);
  rep(i, mid + 1, r) upd(f[i], A[i - l]);
  solve(mid + 1, r);
}
int main() {
  scanf("%s", s + 1); n = strlen(s + 1);
  rep(i, 1, n) c[i] = c[i - 1] + (s[i] == '>');
  fac[0] = 1;
  rep(i, 1, n + 1) fac[i] = 1ll * fac[i - 1] * i % mod;
  fav[n + 1] = qpow(fac[n + 1], mod - 2);
  per(i, n + 1, 1) fav[i - 1] = 1ll * fav[i] * i % mod;
  solve(0, n + 1);
  f[n + 1] = 1ll * fac[n + 1] * f[n + 1] % mod;
  printf("%d\n", f[n + 1]);
  return 0;
}