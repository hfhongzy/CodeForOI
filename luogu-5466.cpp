#include <algorithm>
#include <cstring>
#include <vector>
#include <cstdio>
using namespace std;
typedef long long ll;
const int N = 2e6 + 10, mod = 998244353;
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
int n, A[N], B[N];
bool use[N];
char s[N];
int main() {
   scanf("%s", s + 1); n = strlen(s + 1);
   for(int i = 1; i <= n; i ++) A[i] = (s[i] == '0');
   for(int i = 1; i <= n; i ++) B[n - i] = (s[i] == '1');
   InitNTT(n * 2); NTT(A, w); NTT(B, w);
   for(int i = 0; i < len; i ++) A[i] = 1ll * A[i] * B[i] % mod;
   NTT(A, inv_w);
   for(int i = 0; i <= n * 2; i ++) if(A[i]) {
      use[abs(i - n)] = 1;
   }
   ll res = 0;
   for(int i = 1; i < n; i ++) {
      bool tag = 1;
      for(int j = n - i; j <= n; j += n - i) {
         if(use[j]) { tag = 0; break ; }
      }
      if(tag) res ^= (ll) i * i;
   }
   printf("%lld\n", res ^ ((ll) n * n));
   return 0;
}
/*
若01分别x, y, |x - y| = 0 (mod (n - len))，len不行。
*/