#include <algorithm>
#include <cstring>
#include <cstdio>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int mod = 998244353;
const int N = 1e6 + 10;
int W[N], iW[N], rev[N], len;
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
   int g = qpow(3, (mod - 1) / len);
   W[0] = iW[0] = 1;
   for(int i = 1; i < len; i ++) W[i] = iW[len - i] = 1ll * W[i - 1] * g % mod;
}
void NTT(int *a, const int *w) {
   for(int i = 1; i < len; i ++) if(i < rev[i]) swap(a[i], a[rev[i]]);
   for(int i = 1; i < len; i <<= 1) {
      for(int t = len / (i << 1), j = 0; j < len; j += i << 1) {
         const int *wn = w;
         for(int k = 0; k < i; k ++, wn += t) {
            int p = a[j + k], q = 1ll * *wn * a[j + k + i] % mod;
            a[j + k] = (p + q) % mod; a[j + k + i] = (p - q + mod) % mod;
         }
      }
   }
   if(w == iW) {
      int inv = mod - (mod - 1) / len;
      for(int i = 0; i < len; i ++) {
         a[i] = 1ll * a[i] * inv % mod;
      }
   }
}
char s[N];
struct node {
   int a[N], n;
   void get() {
      scanf("%s", s + 1);
      n = strlen(s + 1);
      for(int i = 0; i < n; i ++) {
         a[i] = s[n - i] & 15;
      }
   }
   void add(int k) {
      a[n] = 0; a[0] += k;
      for(int i = 0; i < n && a[i] >= 10; i ++) {
         a[i + 1] += a[i] / 10; a[i] %= 10;
      }
      if(a[n]) n ++;
   }
   node operator * (const node &b) {
      static int A[N], B[N]; InitNTT(n + b.n - 2);
      for(int i = 0; i < len; i ++) A[i] = i < n ? a[i] : 0;
      for(int i = 0; i < len; i ++) B[i] = i < n ? b.a[i] : 0;
      NTT(A, W); NTT(B, W);
      for(int i = 0; i < len; i ++) A[i] = 1ll * A[i] * B[i] % mod;
      NTT(A, iW);
      node ans; ans.n = n + b.n + 10;
      for(int i = 0; i < ans.n; i ++) ans.a[i] = 0;
      for(int i = 0; i < ans.n; i ++) {
         if(i < n + b.n - 1) ans.a[i] += A[i];
         ans.a[i + 1] += ans.a[i] / 10;
         ans.a[i] %= 10;
      }
      while(ans.n > 1 && !ans.a[ans.n - 1]) ans.n --;
      return ans;
   }
   node divn(int x) {
      node ans; ans.n = n; int r = 0;
      for(int i = n - 1; i >= 0; i --) {
         ans.a[i] = (r * 10 + a[i]) / x;
         r = (r * 10 + a[i]) % x;
      }
      while(ans.n > 1 && !ans.a[ans.n - 1]) ans.n --;
      return ans;
   }
   void out() {
      bool fir = 1;
      for(int i = n - 1; i >= 0; i --) {
         if(a[i] || !i) fir = 0;
         if(!fir) printf("%d", a[i]);
      }
      putchar('\n');
   }
} a, b, c, d;
int main() {
   a.get(); b = c = d = a;
   a.add(1); b.add(2); c.add(3); d.add(4);
   a = a * b * c * d; a = a.divn(24); a.out();
   return 0;
}