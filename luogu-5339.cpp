#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 2e4 + 10, mod = 998244353;
int len, rev[N], W[N], iW[N], ntta[N], nttb[N], inv[N];
inline int add(int x, int y) { return x + y >= mod ? x + y - mod : x + y; }
inline int dec(int x, int y) { return x - y < 0 ? x - y + mod : x - y; }
int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = 1ll * a * a % mod)
      if(b & 1) ans = 1ll * ans * a % mod;
   return ans;
}
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
      for(int i = 0; i < len; i ++)
         a[i] = 1ll * a[i] * inv % mod;
   }
}
#define poly vector<int>
poly operator * (const poly &a, const poly &b) {
   int deg = (int) a.size() + b.size() - 2; InitNTT(deg);
   for(int i = 0; i < len; i ++) ntta[i] = i < a.size() ? a[i] : 0;
   for(int i = 0; i < len; i ++) nttb[i] = i < b.size() ? b[i] : 0;
   NTT(ntta, W); NTT(nttb, W);
   for(int i = 0; i < len; i ++) ntta[i] = 1ll * ntta[i] * nttb[i] % mod;
   NTT(ntta, iW);
   poly ans(deg + 1);
   for(int i = 0; i <= deg; i ++) ans[i] = ntta[i];
   return ans;
}
int n, a, b, c, d, fac[N], fav[N];
int C(int n, int m) {
   return n < m ? 0 : 1ll * fac[n] * fav[m] % mod * fav[n - m] % mod;
}
void binom(int n) {
   fac[0] = 1;
   for(int i = 1; i <= n; i ++) fac[i] = 1ll * fac[i - 1] * i % mod;
   fav[n] = qpow(fac[n], mod - 2);
   for(int i = n; i >= 1; i --) fav[i - 1] = 1ll * fav[i] * i % mod;
}
int solve(int a, int b, int c, int d, int n) {
   if(a < 0 || b < 0 || c < 0 || d < 0) return 0;
   poly A(a + 1), B(b + 1), C(c + 1), D(d + 1);
   for(int i = 0; i <= a; i ++) A[i] = fav[i];
   for(int i = 0; i <= b; i ++) B[i] = fav[i];
   for(int i = 0; i <= c; i ++) C[i] = fav[i];
   for(int i = 0; i <= d; i ++) D[i] = fav[i];
   return 1ll * fac[n] * (A * B * C * D)[n] % mod;
}
int main() {
   cin >> n >> a >> b >> c >> d;
   binom(max(n, max(a, max(b, max(c, d)))));

   int ans = 0;
   for(int i = 0; (i << 2) <= n; i ++) {
      int res = 1ll * C(n - 3 * i, i) * solve(a - i, b - i, c - i, d - i, n - (i << 2)) % mod;
      if(!res) break ;
      ans = (i & 1) ? dec(ans, res) : add(ans, res);
   }
   cout << ans << endl;
   return 0;
}