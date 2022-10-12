#include <algorithm>
#include <cstdio>
#include <vector>
#include <cmath>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 4e5 + 10, mod = 998244353;
int len, rev[N], W[N], iW[N], ntta[N], nttb[N], inv[N];
inline int add(int x, int y) {
   return x + y >= mod ? x + y - mod : x + y;
}
inline int dec(int x, int y) {
   return x - y < 0 ? x - y + mod : x - y;
}
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
void print(const poly &a) {
   for(int i = 0; i < (int) a.size(); i ++) {
      printf("%d ", a[i]);
   }
   putchar('\n');
}
poly Lim(int n, poly a) {
   a.resize(n); return a;
}
poly operator + (const poly &a, const poly &b) {
   poly ans(max(a.size(), b.size()));
   for(int i = 0; i < (int) ans.size(); i ++) {
      ans[i] = add(i < a.size() ? a[i] : 0, i < b.size() ? b[i] : 0);
   }
   return ans;
}
poly operator - (const poly &a, const poly &b) {
   poly ans(max(a.size(), b.size()));
   for(int i = 0; i < (int) ans.size(); i ++) {
      ans[i] = dec(i < a.size() ? a[i] : 0, i < b.size() ? b[i] : 0);
   }
   return ans;
}
poly operator * (int k, poly a) {
   if(k == 1) return a;
   for(int i = 0; i < (int) a.size(); i ++)
      a[i] = 1ll * k * a[i] % mod;
   return a;
}
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
poly Inv(poly a, int n = -1) { //mod x^n
   if(n == -1) n = a.size();
   if(n == 1) return poly(1, qpow(a[0], mod - 2));
   a.resize(n);
   poly f0 = Inv(a, (n + 1) >> 1);
   return Lim(n, 2 * f0 - f0 * f0 * a);
}
int fac[N], fav[N], ans[N];
void binom(int n) {
   fac[0] = 1;
   for(int i = 1; i <= n; i ++) fac[i] = 1ll * fac[i - 1] * i % mod;
   fav[n] = qpow(fac[n], mod - 2);
   for(int i = n; i >= 1; i --) fav[i - 1] = 1ll * fav[i] * i % mod;
}
void prework(int n) {
   binom(n);
   poly F(n + 1);
   for(int i = 1; i <= n; i ++) F[i] = fav[i];
   poly iF = Inv(poly(1, 1) - F), A = Lim(n + 1, Lim(n + 1, F * iF) * iF);
   for(int i = 0; i <= n; i ++) iF[i] = 1ll * iF[i] * fac[i] % mod;
   for(int i = 0; i <= n; i ++) A[i] = 1ll * A[i] * fac[i] % mod;   
   for(int i = 1; i <= n; i ++) ans[i] = 1ll * A[i] * qpow(iF[i], mod - 2) % mod;
}
int main() {
   prework(1e5);
   int test; scanf("%d", &test);
   while(test --) {
      int n; scanf("%d", &n);
      printf("%d\n", ans[n]);
   }
   return 0;
}