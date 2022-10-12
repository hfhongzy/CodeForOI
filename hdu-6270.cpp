#include <algorithm>
#include <vector>
#include <cstdio>
#include <cmath>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10, mod = 998244353, _g = 3;
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
int fac[N], fav[N], a[N], b[N], n = 1e5, m, A[N], B[N];
vector<int> poly[N];
int C(int n, int m) {
  return n < m ? 0 : 1ll * fac[n] * fav[m] % mod * fav[n - m] % mod;
}
vector<int> solve(int l, int r) {
  if(l == r) return poly[l];
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
  fac[0] = 1;
  for(int i = 1; i <= n; i ++) fac[i] = (ll) fac[i - 1] * i % mod;
  fav[n] = qpow(fac[n], mod - 2);
  for(int i = n; i >= 1; i --) fav[i - 1] = (ll) fav[i] * i % mod;
  int test; scanf("%d", &test);
  while(test --) {
    n = 0; scanf("%d", &m);
    for(int i = 1; i <= m; i ++) {
      scanf("%d%d", a + i, b + i); n += a[i];
      poly[i].resize(min(a[i], b[i]) + 1);
      for(int j = 0; j < (int) poly[i].size(); j ++) {
        poly[i][j] = 1ll * C(a[i], j) * C(b[i], j) % mod * fac[j] % mod;
      }
    }
    vector<int> ans = solve(1, m);
    int res = 0;
    for(int i = 0; i <= n; i ++) {
      if(i >= ans.size()) break ;
      (res += (i & 1 ? mod - 1ll : 1ll) * ans[i] % mod * fac[n - i] % mod) %= mod;
    }
    printf("%d\n", res);
  }
  return 0;
}