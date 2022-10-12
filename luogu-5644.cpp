#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;
typedef long long ll;
const int N = 4e5 + 10, mod = 998244353;
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
int n, s, a[N], A[N], B[N];
vector<int> solve(int l, int r) {
   if(l == r) {
      vector<int> res(a[l] + 1);
      res[0] = 1; res[a[l]] = mod - 1;
      return res;
   }
   int mid = (l + r) >> 1;
   vector<int> ls = solve(l, mid), rs = solve(mid + 1, r);
   int lim = (int) ls.size() + rs.size() - 2; InitNTT(lim);
   for(int i = 0; i < len; i ++) A[i] = i < ls.size() ? ls[i] : 0;
   for(int i = 0; i < len; i ++) B[i] = i < rs.size() ? rs[i] : 0;
   NTT(A, w); NTT(B, w);
   for(int i = 0; i < len; i ++) A[i] = 1ll * A[i] * B[i] % mod;
   NTT(A, inv_w); ls.clear(); ls.resize(lim + 1);
   for(int i = 0; i <= lim; i ++) ls[i] = A[i];
   return ls;
}
int main() {
   scanf("%d", &n);
   for(int i = 1; i <= n; i ++) { scanf("%d", a + i); s += a[i]; }
   vector<int> vec = solve(2, n);
   int res = 0;
   for(int i = 0; i <= s - a[1]; i ++) {
      (res += 1ll * vec[i] * a[1] % mod * qpow(a[1] + i, mod - 2) % mod) %= mod;
   }
   printf("%d\n", res);
   return 0;
}