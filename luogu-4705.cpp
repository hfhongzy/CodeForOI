#include <algorithm>
#include <cstdio>
#include <vector> 
using namespace std;
typedef long long ll;
const int N = 4e5 + 10;
const int mod = 998244353;
int rev[N], len;
ll w[N], inv_w[N], inv[N], fac[N], fav[N];
int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = (ll) a * a % mod)
      if(b & 1) ans = (ll) ans * a % mod;
   return ans;
}
void InitNTT(int n) {
   int k = 0;
   for(len = 1; len <= n; len <<= 1) k ++;
   for(int i = 1; i < len; i ++)
      rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
   w[0] = inv_w[0] = 1;
   ll v = qpow(3, (mod - 1) / len);
   for(int i = 1; i < len; i ++)
      inv_w[len - i] = w[i] = w[i - 1] * v % mod;
}
void NTT(ll *a, const ll *w) {
   for(int i = 1; i < len; i ++)
      if(i < rev[i]) swap(a[i], a[rev[i]]);
   for(int i = 1; i < len; i <<= 1) {
      for(int j = 0, t = len / (i << 1); j < len; j += i << 1) {
         const ll *wn = w;
         for(int k = j; k < j + i; k ++, wn += t) {
            ll t1 = a[k], t2 = *wn * a[k + i] % mod;
            a[k] = (t1 + t2) % mod; a[k + i] = (t1 - t2) % mod;
         }
      }
   }
   if(w == inv_w)
      for(int i = 0, v = - (mod - 1) / len; i < len; i ++)
         (a[i] *= v) %= mod;
}
void cpyto(const ll *from, ll *to, int n) {
   for(int i = 0; i < n; i ++) to[i] = from[i];
   for(int i = n; i < len; i ++) to[i] = 0;
}
//AB = 1 (mod x^n), b[n], b[n + 1], ... will not be modified
void Inv(const ll *a, int n, ll *b) {
   if(n == 1) { b[0] = qpow(a[0], mod - 2); return ; }
   int m = (n + 1) >> 1; Inv(a, m, b);
   static ll ta[N], tb[N]; InitNTT(n * 2);
   cpyto(a, ta, n); cpyto(b, tb, m);
   NTT(ta, w); NTT(tb, w);
   for(int i = 0; i < len; i ++)
      (tb[i] *= 2 - tb[i] * ta[i] % mod) %= mod;
   NTT(tb, inv_w);
   for(int i = 0; i < n; i ++) b[i] = tb[i];
}
//Ln(A(x)) = B(x) (mod x^n)
//Int(A'(x) / A(x)) = B(x)
void Ln(const ll *a, int n, ll *b) {
   static ll t1[N], t2[N];
   Inv(a, n, t1); InitNTT(n * 2);
   for(int i = n; i < len; i ++) t1[i] = 0;
   for(int i = 1; i < n; i ++) t2[i - 1] = a[i] * i % mod;
   for(int i = n - 1; i < len; i ++) t2[i] = 0;
   NTT(t1, w); NTT(t2, w);
   for(int i = 0; i < len; i ++) (t1[i] *= t2[i]) %= mod;
   NTT(t1, inv_w); b[0] = 0;
   for(int i = 1; i < n; i ++) b[i] = t1[i - 1] * inv[i] % mod;
}
int n, m, t;
ll a[N], b[N], f[N], g[N]; 
vector<ll> conv(const vector<ll> &a, const vector<ll> &b) {
   int n = (int) a.size() - 1 + b.size() - 1;
   vector<ll> ans(n + 1); InitNTT(n);
   static ll A[N], B[N];
   for(int i = 0; i < len; i ++) A[i] = i < a.size() ? a[i] : 0;
   for(int i = 0; i < len; i ++) B[i] = i < b.size() ? b[i] : 0;
   NTT(A, w); NTT(B, w);
   for(int i = 0; i < len; i ++) A[i] = A[i] * B[i] % mod;
   NTT(A, inv_w);
   for(int i = 0; i <= n; i ++) ans[i] = A[i];
   return ans;
}
vector<ll> prod(ll *a, int l, int r) {
   if(l == r) {
      vector<ll> res(2); res[0] = 1; res[1] = - a[l];
      return res;
   }
   int mid = (l + r) >> 1;
   return conv(prod(a, l, mid), prod(a, mid + 1, r));
}
void solve(ll *a, int n, ll *f) {
   vector<ll> T = prod(a, 1, n);
   static ll A[N], B[N];
   for(int i = 0; i <= n; i ++) A[i] = T[i];
   for(int i = n + 1; i <= t; i ++) A[i] = 0;
   Ln(A, t + 1, B); B[0] = n;
   for(int i = 1; i <= t; i ++) B[i] = B[i] * (mod - i) % mod;
   for(int i = 0; i <= t; i ++) f[i] = B[i];
}
int main() {
   scanf("%d%d", &n, &m);
   for(int i = 1; i <= n; i ++) scanf("%lld", a + i);
   for(int i = 1; i <= m; i ++) scanf("%lld", b + i);
   scanf("%d", &t);
   fac[0] = 1;
   for(int i = 1; i <= t; i ++) fac[i] = fac[i - 1] * i % mod;
   fav[t] = qpow(fac[t], mod - 2);
   for(int i = t; i >= 1; i --) fav[i - 1] = fav[i] * i % mod;
   inv[1] = 1;
   for(int i = 2, lm = max(t, max(n, m)); i <= lm; i ++)
      inv[i] = - (mod / i) * inv[mod % i] % mod;
   solve(a, n, f); solve(b, m, g);
   static ll A[N], B[N];
   for(int i = 0; i <= t; i ++) A[i] = f[i] * fav[i] % mod;
   for(int i = 0; i <= t; i ++) B[i] = g[i] * fav[i] % mod;
   InitNTT(t * 2); NTT(A, w); NTT(B, w);
   for(int i = 0; i < len; i ++) A[i] = A[i] * B[i] % mod;
   NTT(A, inv_w);
   ll inm = qpow((ll) n * m % mod, mod - 2);
   for(int i = 1; i <= t; i ++) {
      ll res = A[i] * inm % mod * fac[i] % mod;
      printf("%lld\n", (res + mod) % mod);
   }
   return 0;
}