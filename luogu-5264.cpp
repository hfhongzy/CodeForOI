#include <algorithm>
#include <cstdio>
#include <vector>
#include <cmath>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 4e5 + 10, mod = 998244353, ii = 86583718;
int n, m, len, rev[N], k, W[N], iW[N], ntta[N], nttb[N], inv[N];
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
   len = 1; k = 0;
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
poly operator + (poly a, poly b) {
   poly ans(max(a.size(), b.size()));
   for(int i = 0; i < (int) ans.size(); i ++) {
      ans[i] = add(i < a.size() ? a[i] : 0, i < b.size() ? b[i] : 0);
   }
   return ans;
}
poly operator - (poly a, poly b) {
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
poly operator * (poly a, poly b) {
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
poly Sqrt(poly a, int n = -1) { //mod x^n
   if(n == -1) n = a.size();
   if(n == 1) return poly(1, 1);
   a.resize(n);
   poly f0 = Sqrt(a, (n + 1) >> 1);
   return Lim(n, (f0 * f0 + a) * Inv(2 * f0, n));
}
poly Der(poly a) {
   if(a.size() == 1) return poly(1, 0);
   poly b((int) a.size() - 1);
   for(int i = 0; i < (int) b.size(); i ++) {
      b[i] = (i + 1ll) * a[i + 1] % mod; 
   }
   return b;
}
poly Int(poly a) {
   if(!inv[1]) {
      inv[1] = 1;
      for(int i = 2; i < N; i ++) {
         inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
      }
   }
   poly b((int) a.size() + 1); b[0] = 0;
   for(int i = 1; i < (int) b.size(); i ++) {
      b[i] = 1ll * inv[i] * a[i - 1] % mod;
   }
   return b;
}
poly Ln(poly a, int n = -1) { //a[0] = 1 & n >= a.size() is ok
   if(n == -1) n = a.size();
   return Lim(n, Int(Der(a) * Inv(a, n)));
}
poly Exp(poly a, int n = -1) { //a[0] = 0
   if(n == -1) n = a.size();
   if(n == 1) return poly(1, 1);
   a.resize(n);
   poly f0 = Exp(a, (n + 1) >> 1);
   return Lim(n, f0 * (poly(1, 1) - Ln(f0, n) + a));
}
poly Pow(poly a, int k, int n = -1) { //a[0] = 1
   if(n == -1) n = a.size();
   return Exp(k * Ln(a));
}
poly Sin(poly a, int n = -1) {
   if(n == -1) n = a.size();
   return qpow(2ll * ii % mod, mod - 2) * (Exp(ii * a) - Exp((mod - ii) * a));
}
poly Cos(poly a, int n = -1) {
   if(n == -1) n = a.size();
   return ((mod + 1) >> 1) * (Exp(ii * a) + Exp((mod - ii) * a));
}
int main3() {
   int ty; scanf("%d%d", &n, &ty); n --;
   poly A; A.resize(n + 1);
   for(int i = 0; i <= n; i ++) scanf("%d", &A[i]);
   print(ty == 0 ? Sin(A) : Cos(A));
   return 0;
}