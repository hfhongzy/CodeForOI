#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> poly;
const int N = 524288 + 10, mod = 998244353;
int add(int x, int y) { return (x += y) >= mod ? x - mod : x; }
int dec(int x, int y) { return x - y < 0 ? x - y + mod : x - y; }
int qpow(int a, int b) {
  int ans = 1;
  for(; b >= 1; b >>= 1, a = (ll)a * a % mod)
    if(b & 1) ans = (ll)ans * a % mod;
  return ans;
}
int rev[N], W[N];
int getn(int len) { int n = 1; while(n < len) n <<= 1; return n; } //[0, len - 1]
void prework(int n) {
  for(int i = 1; i < n; i <<= 1) {
    W[i] = 1;
    int w = qpow(3, (mod - 1) / (i << 1));
    for(int j = 1; j < i; j ++)
      W[i + j] = (ll)W[i + j - 1] * w % mod;
  }
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
  for(int i = 0; i < n; i ++) a[i] = (ll)a[i] * inv % mod;
}
poly fix(poly a, int n) { a.resize(n); return a; }
poly Inv(poly a) {
  int sz = a.size();
  poly c(1, qpow(a[0], mod - 2)), t;
  for(int i = 1; i < sz; i <<= 1) {
    t = fix(a, i << 1);
    NTT(t, i << 2, 1); NTT(c, i << 2, 1);
    for(int j = 0; j < (i << 2); j ++)
      c[j] = c[j] * (2 + (mod - t[j]) * (ll)c[j] % mod) % mod;
    NTT(c, i << 2, -1);
    c.resize(i << 1);
  }
  c.resize(sz);
  return c;
}
int newton(int n) { //mod x^n
  poly c(1, 1), a, b, p, q; //p / q
  for(int i = 1; i < n; i <<= 1) {
    a = b = poly(i << 1);
    for(int j = 0; j < i; j ++) a[j << 1] = c[j];
    for(int j = 0; j * 3 < 2 * i; j ++) b[j * 3] = c[j];
    NTT(c, i << 2, 1); NTT(a, i << 2, 1); NTT(b, i << 2, 1);
    p = q = poly(i << 2);
    for(int j = 0; j < (i << 2); j ++) {
      int w = j < (i << 1) ? W[i << 1 | j] : mod - W[i << 1 | j];
      q[j] = ( 3ll * w * ( (ll(c[j]) * c[j] % mod + a[j]) % mod ) + mod - 6 ) % mod;
      p[j] = (w * ( (ll(c[j]) * c[j] % mod * c[j] + 3ll * a[j] * c[j] % mod + 2ll * b[j]) % mod ) % mod + (mod - 6ll) * c[j] % mod + 6ll) % mod;
    }
    NTT(p, i << 2, -1); NTT(q, i << 2, -1);
    q.resize(i << 1); q = Inv(q);
    p.resize(i << 1);
    NTT(p, i << 2, 1); NTT(q, i << 2, 1);
    for(int j = 0; j < (i << 2); j ++) {
      c[j] = (c[j] + (mod - p[j]) * (ll)q[j]) % mod;
    }
    NTT(c, i << 2, -1);
    c.resize(i << 1);
  }
  return c[n - 1];
}
int main() {
  int n; scanf("%d", &n); prework((n + 1) * 2);
  printf("%d\n", newton(n + 1));
  return 0;
}