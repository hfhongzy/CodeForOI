#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int N = 2e5 + 10;
inline int add(int x, int y) { return x + y >= mod ? x + y - mod : x + y; }
inline int dec(int x, int y) { return x - y < 0 ? x - y + mod : x - y; }
int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = (ll) a * a % mod)
      if(b & 1) ans = (ll) ans * a % mod;
   return ans;
}

int n, m, q, maxw, len, rev[N], W[N], iW[N];
struct mat {
   int a[9][9];
   void z0() { rep(i, 1, n) rep(j, 1, n) a[i][j] = 0; }
   void z1() { rep(i, 1, n) rep(j, 1, n) a[i][j] = i == j; }
   mat operator + (mat b) {
      static mat ans; rep(i, 1, n) rep(j, 1, n) ans.a[i][j] = add(a[i][j], b.a[i][j]); return ans;
   }
   mat operator - (mat b) {
      static mat ans; rep(i, 1, n) rep(j, 1, n) ans.a[i][j] = dec(a[i][j], b.a[i][j]); return ans;
   }
   mat operator * (mat b) {
      static mat ans;
      rep(i, 1, n) rep(j, 1, n) {
         ans.a[i][j] = 0; rep(k, 1, n) ans.a[i][j] = (ans.a[i][j] + (ll) a[i][k] * b.a[k][j]) % mod;
      }
      return ans;
   }
   mat operator * (int k) {
      static mat ans;
      rep(i, 1, n) rep(j, 1, n) ans.a[i][j] = (ll) a[i][j] * k % mod;
      return ans;
   }
} m0, m1, m2;
void InitNTT(int n) {
   len = 1; int k = 0;
   while(len <= n) len <<= 1, k ++;
   rep(i, 1, len - 1) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
   int w0 = qpow(3, (mod - 1) / len); W[0] = iW[len] = 1;
   rep(i, 1, len) W[i] = iW[len - i] = 1ll * W[i - 1] * w0 % mod;
}
void NTT(mat *a, const int *W) {
   rep(i, 1, len - 1) if(i < rev[i]) swap(a[i], a[rev[i]]);
   mat p, q;
   for(int i = 1; i < len; i <<= 1) {
      for(int j = 0, t = len / (i << 1); j < len; j += i << 1) {
         const int *wn = W;
         for(int k = 0; k < i; k ++, wn += t) {
            p = a[j + k], q = a[j + k + i] * *wn;
            a[j + k] = p + q; a[j + k + i] = p - q;
         }
      }
   }
   if(W == iW) {
      int inv = mod - (mod - 1) / len;
      for(int i = 0; i < len; i ++)
         a[i] = a[i] * inv;
   }
}
void Inv(int n, const mat *a, mat *ans) {
   if(n == 1) { ans[0].z1(); return; }
   int m = (n + 1) >> 1;
   static mat t[N], ta[N], tb[N]; Inv(m, a, ans); InitNTT(n << 1);
   for(int i = 0; i < m; i ++) ta[i] = ans[i];
   for(int i = m; i < len; i ++) ta[i].z0();
   for(int i = 0; i < n; i ++) tb[i] = a[i];
   for(int i = n; i < len; i ++) tb[i].z0();
   NTT(ta, W); NTT(tb, W);
   for(int i = 0; i < len; i ++) ta[i] = ta[i] * (m2 - tb[i] * ta[i]);
   NTT(ta, iW);
   for(int i = 0; i < n; i ++) ans[i] = ta[i];
}
int main() {
   scanf("%d%d%d%d", &n, &m, &q, &maxw);
   m0.z0(); m1.z1(); m2 = m1 * 2;
   static mat A[N], ans[N]; A[0].z1();
   int u, v, w;
   rep(i, 1, m) {
      scanf("%d%d%d", &u, &v, &w);
      A[w].a[u][v] --;
      if(A[w].a[u][v] < 0) A[w].a[u][v] += mod;
   }
   Inv(maxw + 1, A, ans);
   rep(i, 1, q) {
      scanf("%d%d%d", &u, &v, &w);
      printf("%d\n", ans[w].a[u][v]);
   }
   return 0;
}