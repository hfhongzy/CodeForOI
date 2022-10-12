#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;
const int N = 4e4 + 10, mod = 998244353;
int m, p, n, a, b, c, len, rev[N], W[N], iW[N];
int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = 1ll * a * a % mod)
      if(b & 1) ans = 1ll * ans * a % mod;
   return ans;
}
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
void poly_inv(const int *a, int n, int *b) { //B = A^{-1} (mod x^n)
   if(n == 1) { b[0] = qpow(a[0], mod - 2); return ; }
   int m = (n + 1) >> 1; poly_inv(a, m, b);
   static int ta[N], tb[N]; InitNTT(n * 2);
   for(int i = 0; i < n; i ++) ta[i] = a[i];
   for(int i = n; i < len; i ++) ta[i] = 0;
   for(int i = 0; i < m; i ++) tb[i] = b[i];
   for(int i = m; i < len; i ++) tb[i] = 0;
   NTT(ta, W); NTT(tb, W);
   for(int i = 0; i < len; i ++)
      tb[i] = (mod + 2 - 1ll * tb[i] * ta[i] % mod) * tb[i] % mod;
   NTT(tb, iW);
   for(int i = 0; i < n; i ++) b[i] = tb[i];
}
struct poly {
   vector<int> a;
   poly() {} poly(int n) { a.resize(n); }
   int &operator [](int x) { return a[x]; }
   int size() { return a.size(); }
   poly po(int x) { poly ans(1); ans.a[0] = x; return ans; }
   poly operator + (const poly &b) {
      int n = max(a.size(), b.a.size());
      poly ans(n);
      for(int i = 0; i < n; i ++) {
         ans[i] = ((i < a.size() ? a[i] : 0) + (i < b.a.size() ? b.a[i] : 0)) % p;
      }
      return ans;
   }
   poly operator - (const poly &b) {
      int n = max(a.size(), b.a.size());
      poly ans(n);
      for(int i = 0; i < n; i ++) {
         ans[i] = (((i < a.size() ? a[i] : 0) - (i < b.a.size() ? b.a[i] : 0)) + p) % p;
      }
      return ans;
   }
   poly operator * (const poly &b) {
      int n = (int) a.size() + b.a.size() - 2; InitNTT(n);
      static int A[N], B[N];
      for(int i = 0; i < len; i ++) A[i] = i < a.size() ? a[i] : 0;
      for(int i = 0; i < len; i ++) B[i] = i < b.a.size() ? b.a[i] : 0;
      NTT(A, W); NTT(B, W);
      for(int i = 0; i < len; i ++) A[i] = 1ll * A[i] * B[i] % mod;
      NTT(A, iW);
      poly ans(min(n, m) + 1);
      for(int i = 0; i < (int) ans.size(); i ++) ans.a[i] = A[i] % p;
      return ans;
   }
   poly inv(int m) {
      static int A[N], B[N];
      for(int i = 0; i < m; i ++) A[i] = i < a.size() ? a[i] : 0;
      poly_inv(A, m, B); poly ans(m);
      for(int i = 0; i < m; i ++) ans[i] = B[i] % p;
      return ans;
   }
   poly Pow(int b) {
      poly a = *this, ans = po(1);
      for(; b >= 1; b >>= 1, a = a * a)
         if(b & 1) ans = ans * a;
      return ans;
   }
} A;
//S=A+A^2+A^n = A(1 - A^n)/(1-A)
int calc(ll x) {
   return (a * x * x + b * x + c) % p;
}
int main() {
   scanf("%d%d%d%d%d%d", &m, &p, &n, &a, &b, &c);
   A.a.resize(m + 1);
   for(int i = 1; i <= m; i ++) A.a[i] = calc(i);
   poly T = A * (A.po(1) - A.Pow(n)) * ( (A.po(1) - A).inv(m + 1) );
   printf("%d\n", T.a[m] % p);
   return 0;
}