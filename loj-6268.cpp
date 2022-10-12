#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
typedef vector<int> poly;
const int N = 4e5 + 10;
const int mod = 998244353;
int add(int x, int y) { return (x += y) >= mod ? x - mod : x; }
int dec(int x, int y) { return x - y < 0 ? x - y + mod : x - y; }
int qpow(int a, int b) {
  int ans = 1;
  for(; b >= 1; b >>= 1, a = (ll)a * a % mod)
    if(b & 1) ans = (ll)ans * a % mod;
  return ans;
}
int rev[N], W[N], inv[N];
int getn(int len) { int n = 1; while(n < len) n <<= 1; return n; }
void prework(int n) {
  for(int i = 1; i < n; i <<= 1) {
    W[i] = 1;
    int w = qpow(3, (mod - 1) / (i << 1));
    for(int j = 1; j < i; j ++)
      W[i + j] = (ll)W[i + j - 1] * w % mod;
  }
  inv[1] = 1;
  for(int i = 2; i <= n; i ++) inv[i] = (mod - mod / i) * (ll)inv[mod % i] % mod;
}
void NTT(poly &a, int n, int op) {
  a.resize(n);
  for(int i = 1; i < n; i ++)
    if(i < (rev[i] = (rev[i >> 1] >> 1) | (i & 1 ? n >> 1 : 0)))
      swap(a[i], a[rev[i]]);
  for(int i = 1; i < n; i <<= 1) {
    for(int j = 0; j < n; j += i << 1) {
      for(int k = 0; k < i; k ++) {
        int q = (ll)W[i + k] * a[j + k + i] % mod;
        a[j + k + i] = add(a[j + k], mod - q); a[j + k] = add(a[j + k], q);
      }
    }
  }
  if(op == 1) return ;
  reverse(a.begin() + 1, a.end());
  int inv = mod - (mod - 1) / n;
  rep(i, 0, n - 1) a[i] = (ll)a[i] * inv % mod;
}
poly fix(poly a, int n) { a.resize(n); return a; }
poly operator + (poly a, poly b) {
  if(a.size() < b.size()) a.resize(b.size());
  for(int i = 0; i < int(b.size()); i ++) a[i] = add(a[i], b[i]);
  return a;
}
poly operator - (poly a, poly b) {
  if(a.size() < b.size()) a.resize(b.size());
  for(int i = 0; i < int(b.size()); i ++) a[i] = dec(a[i], b[i]);
  return a;
}
poly operator * (poly a, int b) {
  for(int i = 0; i < int(a.size()); i ++) a[i] = (ll)a[i] * b % mod;
  return a;
}
poly operator * (int b, poly a) { return a * b; }
poly operator * (poly a, poly b) {
  int t = a.size() + b.size() - 1, n = getn(t);
  NTT(a, n, 1); NTT(b, n, 1);
  rep(i, 0, n - 1) a[i] = (ll)a[i] * b[i] % mod;
  NTT(a, n, -1); a.resize(t);
  return a;
}
poly Der(poly a) {
  for(int i = 0; i < int(a.size()) - 1; i ++)
    a[i] = a[i + 1] * (i + 1ll) % mod;
  a.pop_back();
  return a;
}
poly Int(poly a) {
  a.pb(0);
  for(int i = int(a.size()) - 1; i >= 1; i --)
    a[i] = (ll)a[i - 1] * inv[i] % mod;
  a[0] = 0;
  return a;
}
poly Inv(poly a) {
  int sz = a.size();
  poly c(1, qpow(a[0], mod - 2)), t;
  for(int i = 1; i < sz; i <<= 1) {
    NTT(t = fix(a, i << 1), i << 2, 1); NTT(c, i << 2, 1);
    for(int j = 0; j < (i << 2); j ++)
      c[j] = (2 * c[j] - (ll)t[j] * c[j] % mod * c[j] % mod + mod) % mod;
    NTT(c, i << 2, -1); c.resize(i << 1);
  }
  c.resize(sz);
  return c;
}
poly Ln(poly a) {
  return Int(fix(Der(a) * Inv(a), a.size() - 1));
}
poly Exp(poly a) {
  int sz = a.size();
  poly c(1, 1); a[0] = add(a[0], 1);
  for(int i = 1; i < sz; i <<= 1) {
    c = c * (fix(a, i << 1) - Ln(fix(c, i << 1)));
    c.resize(i << 1);
  }
  c.resize(sz);
  return c;
}
int main() {
	int n;
  scanf("%d", &n);
  prework((n + 1) * 2);
  poly A(n + 1);
  inv[1] = 1;
	rep(i, 2, n)
		inv[i] = (mod - mod / i) * (ll)inv[mod % i] % mod;
	rep(i, 1, n)
		for(int j = 1; i * j <= n; j ++)
			A[i * j] = add(A[i * j], inv[j]);
	A = Exp(A);
	rep(i, 1, n) printf("%d\n", A[i]);
	return 0;
}