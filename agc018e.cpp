#include <bits/stdc++.h>
#define pb push_back
#define LOG(FMT...) fprintf(stderr, FMT);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 2e6 + 20;
const int mod = 1e9 + 7;
int qpow(int a, int b) {
  int ans = 1;
  for(; b >= 1; b >>= 1, a = (ll)a * a % mod)
    if(b & 1) ans = (ll)ans * a % mod;
  return ans;
}
int fac[N], fav[N]; 
int C(int n, int m) {
  return n < m ? 0 : (ll)fac[n] * fav[m] % mod * fav[n - m] % mod;
}
void binom(int n) {
  fac[0] = 1;
  rep(i, 1, n) fac[i] = (ll)fac[i - 1] * i % mod;
  fav[n] = qpow(fac[n], mod - 2);
  per(i, n, 1) fav[i - 1] = (ll)fav[i] * i % mod;
}
struct point {
  int x, y, w;
} a[4], b[4];
int x[8], y[8];
int path(int u, int v) { return C(u + v, v); }
int solve(int x1, int y1, int x2, int y2) {
  int res = 0;
  rep(u, x[3], x[4]) {
    res = (res + (ll)path(u - x1, y[3] - 1 - y1) * path(x2 - u, y2 - y[3]) % mod * -(u + y[3])) % mod; //down
    res = (res + (ll)path(u - x1, y[4] - y1) * path(x2 - u, y2 - y[4] - 1) % mod * (u + y[4] + 1)) % mod; //up
  }
  rep(v, y[3], y[4]) {
    res = (res + (ll)path(x[3] - x1 - 1, v - y1) * path(x2 - x[3], y2 - v) % mod * -(x[3] + v)) % mod; //left
    res = (res + (ll)path(x[4] - x1, v - y1) * path(x2 - x[4] - 1, y2 - v) % mod * (x[4] + v + 1)) % mod; //right
  }
  return res;
}
int main() {
  rep(i, 1, 6) scanf("%d", x + i);
  rep(i, 1, 6) scanf("%d", y + i);
  binom(max(x[6] - x[1], y[6] - y[1]) * 2 + 2);
  a[0] = {x[2], y[2], 1};
  a[1] = {x[1] - 1, y[2], -1};
  a[2] = {x[2], y[1] - 1, -1};
  a[3] = {x[1] - 1, y[1] - 1, 1};

  b[0] = {x[5], y[5], 1};
  b[1] = {x[6] + 1, y[5], -1};
  b[2] = {x[5], y[6] + 1, -1};
  b[3] = {x[6] + 1, y[6] + 1, 1};

  int ans = 0;
  rep(s, 0, 3) rep(t, 0, 3) {
    (ans += a[s].w * b[t].w * solve(a[s].x, a[s].y, b[t].x, b[t].y)) %= mod;
  }
  if(ans < 0) ans += mod;
  printf("%d\n", ans);
  return 0;
}