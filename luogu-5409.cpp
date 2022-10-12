#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 131072 * 2 + 10, mod = 167772161;
int n, m, len, rev[N], k, W[N], iW[N], ntta[N], nttb[N], inv[N], fac[N];
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
poly Der(poly a) {
   if(a.size() == 1) return poly(1, 0);
   poly b((int) a.size() - 1);
   for(int i = 0; i < (int) b.size(); i ++) {
      b[i] = (i + 1ll) * a[i + 1] % mod; 
   }
   return b;
}
poly Int(poly a) {
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
poly Push0(poly a, int k, int n) {
   poly ans(n);
   for(int i = 0; i < n; i ++) {
      ans[i] = i < k ? 0 : a[i - k];
   }
   return ans;
}
poly Power(poly a, int k, int n = -1) {
   if(n == -1) n = a.size();
   int r = 0;
   for(; r < (int) a.size() && !a[r]; r ++) ;
   if(r == a.size()) return poly(1, 0);
   if(1ll * k * r >= n) return poly(n, 0);
   poly A;
   for(int i = r; i < (int) a.size(); i ++) A.push_back(a[i]);
   int t = A[0];
   A = qpow(t, k) * Exp(k * Ln(qpow(t, mod - 2) * A));
   return Push0(A, r * k, n);
}
int main() {
   int n, m, iv = 1;
   scanf("%d%d", &n, &m);
   for(int i = 1; i <= m; i ++) iv = 1ll * iv * i % mod;
   iv = qpow(iv, mod - 2);
   inv[1] = 1;
   for(int i = 2; i <= n; i ++) {
      inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
   }
   fac[0] = 1;
   for(int i = 1; i <= n; i ++) {
      fac[i] = 1ll * fac[i - 1] * i % mod;
   }
   poly X(2); X[0] = 0; X[1] = 1;
   poly A = Power(Exp(X, n + 1) - poly(1, 1), m);
   for(int i = 0; i <= n; i ++) {
      printf("%d%c", (int)(1ll * A[i] * fac[i] % mod * iv % mod), " \n"[i == n]);
   }
   return 0;
}