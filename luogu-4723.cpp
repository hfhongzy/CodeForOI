#include <algorithm>
#include <cstdio>
#include <vector>
#include <cmath>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
#define debug(x) printf("%s = %d\n", #x, (int) x)
using namespace std;
typedef long long ll;
const int N = 32000 * 6 + 10, mod = 998244353;
int len, rev[N], W[N], iW[N], ntta[N], nttb[N];
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
poly Lim(int n, poly a) { a.resize(n); return a; }
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
poly Rev(poly a) { reverse(a.begin(), a.end()); return a; }
poly Temp;
poly operator / (poly a, poly b) {
   int sz = a.size() - b.size() + 1;
   static bool tag;
   if(!tag) { Temp = Inv(Rev(b)); tag = 1; }
   return Rev(Lim(sz, Rev(a) * Temp));
}
poly operator % (poly a, poly b) {
   if(a.size() < b.size()) return a;
   return Lim((int) b.size() - 1, a - (a / b) * b);
}
int n, k, f[N], a[N];
poly P;
poly BPow(int n, poly P) { //x^n mod P
   poly A(2); A[0] = 0; A[1] = 1;
   poly ans(1, 1);
   for(; n >= 1; n >>= 1, A = A * A % P)
      if(n & 1) ans = ans * A % P;
   return ans;
}
int main() {
   scanf("%d%d", &n, &k);
   rep(i, 1, k) scanf("%d", f + i), f[i] = (f[i] % mod + mod) % mod;
   rep(i, 0, k - 1) scanf("%d", a + i), a[i] = (a[i] % mod + mod) % mod;
   P.resize(k + 1); P[k] = mod - 1;
   rep(i, 0, k - 1) P[i] = f[k - i];
   poly G = BPow(n, P);
   int ans = 0;
   rep(i, 0, k - 1) ans = add(ans, 1ll * G[i] * a[i] % mod);
   printf("%d\n", ans);
   return 0;
}