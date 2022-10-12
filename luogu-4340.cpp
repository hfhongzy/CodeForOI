#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 1e5 + 10, mod = 1e9 + 7;
int n, q, ans, a[N], p[N];
int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = 1ll * a * a % mod)
      if(b & 1) ans = 1ll * ans * a % mod;
   return ans;
}
int sum[N << 2], tag[N << 2];
void mktag(int u, int x) {
   tag[u] = 1ll * tag[u] * x % mod;
   sum[u] = 1ll * sum[u] * x % mod;
}
void pdown(int u) {
   if(tag[u] ^ 1) {
      mktag(u << 1, tag[u]);
      mktag(u << 1 | 1, tag[u]);
      tag[u] = 1;
   }
}
void build(int u, int l, int r) {
   tag[u] = 1;
   if(l == r) {
      sum[u] = 1ll * p[l] * qpow(3, n - 1 - l) % mod;
      return ;
   }
   int mid = (l + r) >> 1;
   build(u << 1, l, mid);
   build(u << 1 | 1, mid + 1, r);
   sum[u] = (sum[u << 1] + sum[u << 1 | 1]) % mod;
}
void update(int u, int l, int r, int ql, int qr, int val) {
   if(l == ql && r == qr) { mktag(u, val); return ; }
   int mid = (l + r) >> 1; pdown(u);
   if(qr <= mid) update(u << 1, l, mid, ql, qr, val);
   else if(ql > mid) update(u << 1 | 1, mid + 1, r, ql, qr, val);
   else {
      update(u << 1, l, mid, ql, mid, val);
      update(u << 1 | 1, mid + 1, r, mid + 1, qr, val);
   }
   sum[u] = (sum[u << 1] + sum[u << 1 | 1]) % mod;
}
int main() {
   const int inv3 = qpow(3, mod - 2);
   scanf("%d%d", &n, &q);
   for(int i = 1; i <= n; i ++) {
      scanf("%d", a + i);
   }
   if(n <= 20 && q <= 20) {
      for(int i = 1; i <= q; i ++) {
         int u, v; scanf("%d%d", &u, &v); a[u] = v;
         int res = 0, pw = qpow(3, n - 1), pd = 1;
         for(int j = 1; j < n; j ++) {
            pw = 1ll * pw * inv3 % mod;
            pd = 1ll * pd * a[j] % mod;
            (res += 1ll * pd * pw % mod) %= mod;
         }
         res = (res + res) % mod;
         pd = 1;
         for(int j = 1; j <= n; j ++) {
            pd = 1ll * pd * a[j] % mod;
         }
         (res += pd) %= mod;
         printf("%d\n", res);
      }
   } else {
      for(int i = 1; i <= n; i ++) 
         p[i] = i == 1 ? a[1] : 1ll * a[i] * p[i - 1] % mod;
      int pd = p[n];
      build(1, 1, n - 1);
      for(int i = 1; i <= q; i ++) {
         int u, v; scanf("%d%d", &u, &v);
         int tr = 1ll * qpow(a[u], mod - 2) * v % mod;
         pd = 1ll * pd * tr % mod;
         if(u < n) update(1, 1, n - 1, u, n - 1, tr); a[u] = v;
         printf("%d\n", (int)( (2ll * sum[1] + pd) % mod ));
      }
   }
   return 0;
}