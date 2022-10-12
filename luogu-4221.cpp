#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 21, mod = 998244353;
int n, m, p, w[N], f[N], d[N], sum[1 << N], invsum[1 << N], cnt[1 << N];
int A[N + 1][1 << N], B[N + 1][1 << N];
bool a[N][N], tag[1 << N];
int pw(int x) { return p == 0 ? 1 : (p == 1 ? x : 1ll * x * x % mod); }
void add(int &x, const int &y) { (x += y) >= mod ? x -= mod : 0; }
int upd(const int &x) { return x >= mod ? x - mod : x; }
int find(int u) { return u == f[u] ? u : f[u] = find(f[u]); }
void unite(int u, int v) { f[find(u)] = find(v); }
int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = 1ll * a * a % mod)
      if(b & 1) ans = 1ll * ans * a % mod;
   return ans;
}
void fwt(int *a, int len) {
   for(int i = 1; i < len; i <<= 1) {
      for(int j = 0; j < len; j += i << 1) {
         for(int k = 0; k < i; k ++) {
            int p = a[j + k], q = a[j + k + i];
            a[j + k] = upd(p + q); a[j + k + i] = upd(p - q + mod);
         }
      }
   }
}
void Ifwt(int *a, int len) {
   const long long inv2 = (mod + 1) >> 1;
   for(int i = 1; i < len; i <<= 1) {
      for(int j = 0; j < len; j += i << 1) {
         for(int k = 0; k < i; k ++) {
            int p = a[j + k], q = a[j + k + i];
            a[j + k] = (p + q) * inv2 % mod;
            a[j + k + i] = (p - q + mod) * inv2 % mod;
         }
      }
   }
}
int main() {
   scanf("%d%d%d", &n, &m, &p);
   for(int i = 0; i < m; i ++) {
      int u, v; scanf("%d%d", &u, &v);
      u --; v --; a[u][v] = a[v][u] = 1;
   }
   for(int i = 0; i < n; i ++) scanf("%d", w + i);
   for(int i = 1; i < (1 << n); i ++) {
      cnt[i] = cnt[i & (i - 1)] + 1;
      for(int j = 0; j < n; j ++) if(i >> j & 1) {
         add(sum[i], w[j]); d[j] = 0; f[j] = j;
      }
      sum[i] = pw(sum[i]); invsum[i] = qpow(sum[i], mod - 2);
      for(int j = 0; j < n; j ++) if(i >> j & 1) {
         for(int k = j + 1; k < n; k ++) if(i >> k & 1) {
            if(a[j][k]) { d[j] ^= 1; d[k] ^= 1; unite(j, k); }
         }
      }
      int r = 0, d1 = 0;
      for(int j = 0; j < n; j ++) if(i >> j & 1) {
         if((r += find(j) == j) > 1) break ;
         if(d[j]) { d1 = 1; break ; }
      }
      tag[i] = r > 1 || d1;
      if(tag[i]) B[cnt[i]][i] = sum[i];
   }
   for(int i = 1; i <= n; i ++) fwt(B[i], 1 << n);
   A[0][0] = 1; fwt(A[0], 1 << n);
   for(int i = 1; i <= n; i ++) {
      for(int j = 0; j < i; j ++) {
         for(int k = 0; k < (1 << n); k ++) {
            add(A[i][k], 1ll * A[j][k] * B[i - j][k] % mod);
         }
      }
      Ifwt(A[i], 1 << n);
      for(int j = 0; j < (1 << n); j ++) if(cnt[j] == i) {
         A[i][j] = 1ll * A[i][j] * invsum[j] % mod;
      }
      if(i < n) fwt(A[i], 1 << n);
   }
   printf("%d\n", A[n][(1 << n) - 1]);
   return 0;
}