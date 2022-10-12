#include <algorithm>
#include <vector>
#include <cstdio>
#include <cmath>
using namespace std;
typedef long long ll;
const int N = 32000 + 10, mod = 1004535809, _g = 3;
int qpow(int a, int b, int mo = mod) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = (ll) a * a % mo)
      if(b & 1) ans = (ll) ans * a % mo;
   return ans;
}
int rev[N], len, w[N], inv_w[N];
void InitNTT(int n) {
   int k = 0;
   for(len = 1; len <= n; len <<= 1) k ++;
   for(int i = 1; i < len; i ++)
      rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
   w[0] = inv_w[0] = 1;
   int v = qpow(_g, (mod - 1) / len);
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
int n, m, x, s, g, a[N], pw[N], lg[N];
vector<int> mul(const vector<int> &a, const vector<int> &b, const int &mo) {
   static int A[N], B[N];
   for(int i = 0; i < len; i ++) A[i] = i < mo ? a[i] : 0;
   for(int i = 0; i < len; i ++) B[i] = i < mo ? b[i] : 0;
   NTT(A, w); NTT(B, w);
   for(int i = 0; i < len; i ++) A[i] = 1ll * A[i] * B[i] % mod;
   NTT(A, inv_w);
   vector<int> ans(mo);
   for(int i = 0; i < 2 * mo - 1; i ++) (ans[i % mo] += A[i]) %= mod;
   return ans;
}
vector<int> polypow(int *p, int b, int mo) { //A[i]B[j] -> C[(i + j) % mo]
   InitNTT(2 * mo);
   vector<int> a(mo), ans(mo); ans[0] = 1;
   for(int i = 0; i < mo; i ++) a[i] = p[i];
   for(; b >= 1; b >>= 1, a = mul(a, a, mo))
      if(b & 1) ans = mul(ans, a, mo);
   return ans;
}
int main() {
   scanf("%d%d%d%d", &n, &m, &x, &s);
   for(g = 2; g < m; g ++) {
      int x = m - 1; bool tag = 1;
      for(int i = 2; i * i <= x; i ++) if(x % i == 0) {
         if(qpow(g, (m - 1) / i, m) == 1) { tag = 0; break ; }
         while(x % i == 0) x /= i;
      }
      if(tag && x > 1 && qpow(g, (m - 1) / x, m) == 1) tag = 0;
      if(tag) break ;
   }
   pw[0] = 1; lg[1] = 0;
   for(int i = 1; i < m - 1; i ++) {
      pw[i] = pw[i - 1] * g % m;
      lg[pw[i]] = i;
   }
   for(int i = 0; i < s; i ++) {
      int x; scanf("%d", &x); if(x) a[lg[x]] = 1;
   }
   vector<int> res = polypow(a, n, m - 1);
   printf("%d\n", res[lg[x]]);
   return 0;
}