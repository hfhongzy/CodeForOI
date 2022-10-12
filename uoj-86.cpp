#include <bits/stdc++.h>
#define pb push_back
#define debug(...) fprintf(stderr, __VA_ARGS__);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
using ll = __int128;
const int N = 65536 + 5;
const int mod = 998244353;
template<class T>
void read(T &x) {
  x = 0; char c = getchar();
  for(; c < '0' || c > '9'; c = getchar()) ;
  for(; c >= '0' && c <= '9'; c = getchar())
    x = x * 10 + (c & 15);
}
int g, p, ans1[N], ans2[N], ni[N], ri[N], ind[N], pw[N];
int qpow(int a, int b, int p = mod) {
  int ans = 1;
  for(; b >= 1; b >>= 1, a = 1ll * a * a % p)
    if(b & 1) ans = 1ll * ans * a % p;
  return ans;
}
int add(int a, int b) { return (a += b) >= mod ? a - mod : a; }
int dec(int a, int b) { return (a -= b) < 0 ? a + mod : a; }
int get(int sz) { int n = 1; while(n < sz) n <<= 1; return n; }
int un, W[N], rev[N];
void prework(int n) { //size(a + b)
  for(int i = 1; i < n; i <<= 1) {
    int w = qpow(3, (mod - 1) / (i << 1));
    for(int j = W[i] = 1; j < i; j ++)
      W[i + j] = 1ll * W[i + j - 1] * w % mod;
  }
  for(int i = 1; i < n; i ++)
    rev[i] = (rev[i >> 1] >> 1) | (i & 1 ? n >> 1 : 0);
}
void fft(int *a, int n, int op) {
  for(int i = 1; i < n; i ++)
    if(i < rev[i]) swap(a[i], a[rev[i]]);
  for(int i = 1; i < n; i <<= 1) {
    for(int j = 0; j < n; j += i << 1) {
      for(int k = 0; k < i; k ++) {
        int q = 1ll * a[j + k + i] * W[i + k] % mod;
        a[j + k + i] = dec(a[j + k], q); a[j + k] = add(a[j + k], q);
      }
    }
  }
  if(op == 1) return ;
  reverse(a + 1, a + n);
  int inv = mod - (mod - 1) / n;
  for(int i = 0; i < n; i ++) a[i] = 1ll * a[i] * inv % mod;
}
void getg() {
  vector<int> fac;
  int x = p - 1;
  for(int i = 2; i * i <= x; i ++)
    if(x % i == 0) { fac.pb(i); while(x % i == 0) x /= i; }
  if(x > 1) fac.pb(x);
  for(g = 1; g < p; g ++) {
    bool mk = 1;
    for(int &v : fac) if(qpow(g, (p - 1) / v, p) == 1) { mk = 0; break ; }
    if(mk) break ;
  }
  for(int i = 0, z = 1; i < p - 1; i ++, z = z * g % p) ind[z] = i, pw[i] = z;
}
int fac[N], fav[N];
int C(int n, int m) {
  return n < m ? 0 : fac[n] * fav[m] % p * fav[n - m] % p;
}
void binom(int n) {
  fac[0] = 1;
  rep(i, 1, n) fac[i] = fac[i - 1] * i % p;
  fav[n] = qpow(fac[n], p - 2, p);
  per(i, n, 1) fav[i - 1] = fav[i] * i % p;
}
ll l, r, n;
int c[N], d[N], e[N], f0[N], f1[N], g0[N], g1[N];
void solve(ll r, int *ans) {
  if(r < n) { ans[0] = (r + 1) % mod; return ; }
  *ri = 0;
  do { ri[++ *ri] = r % p; r /= p; } while(r);
  fill(f0, f0 + un, 0); fill(f1, f1 + un, 0);
  f1[1] = 1;
  per(k, ri[0], 1) {
    fill(g0, g0 + p, 0); fill(g1, g1 + p, 0);

    fill(c, c + un, 0);
    int t = 0, u, s;
    for(int i = 0; i < p; i ++) !(u = C(i, ni[k])) ? t ++ : c[ind[u]] ++;
    for(int i = 0; i < un; i ++) d[i] = i < p - 1 ? f0[pw[i]] : 0;
    fft(d, un, 1); fft(c, un, 1);
    for(int i = 0; i < un; i ++) d[i] = 1ll * d[i] * c[i] % mod;
    s = 0;
    for(int i = 1; i < p; i ++) s = add(s, f0[i]);
    g0[0] = (g0[0] + 1ll * s * t + 1ll * f0[0] * p) % mod;

    fill(c, c + un, 0);
    t = 0;
    for(int i = 0; i < ri[k]; i ++) !(u = C(i, ni[k])) ? t ++ : c[ind[u]] ++;
    for(int i = 0; i < un; i ++) e[i] = i < p - 1 ? f1[pw[i]] : 0;
    fft(e, un, 1); fft(c, un, 1);
    for(int i = 0; i < un; i ++) d[i] = (d[i] + 1ll * e[i] * c[i]) % mod;
    fft(d, un, -1);
    for(int i = 0; i < 2 * p - 1; i ++) u = pw[i >= p - 1 ? i - (p - 1) : i], g0[u] = add(g0[u], d[i]);
    s = 0;
    for(int i = 1; i < p; i ++) s = add(s, f1[i]);
    g0[0] = (g0[0] + 1ll * s * t + 1ll * f1[0] * ri[k]) % mod;

    t = C(ri[k], ni[k]);
    for(int i = 0; i < p; i ++) u = i * t % p, g1[u] = add(g1[u], f1[i]);

    copy(g0, g0 + p, f0); copy(g1, g1 + p, f1);
  }
  for(int i = 0; i < p; i ++) ans[i] = add(f0[i], f1[i]);
}
int main() {
  read(p); read(n); read(l); read(r);
  getg(); binom(p - 1); un = get(2 * p); prework(un);
  ll t = n;
  do { ni[++ *ni] = t % p; t /= p; } while(t);
  solve(r, ans1);
  solve(l - 1, ans2);
  for(int i = 0; i < p; i ++) {
    // cerr << "i = " << i << ", " << ans1[i] << " & " << ans2[i] << endl;
    printf("%d\n", dec(ans1[i], ans2[i]));
  }
  return 0;
}