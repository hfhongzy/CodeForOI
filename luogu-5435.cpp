#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 5000 + 10;
const int mod = 998244353;
const int M = 1000;
int n, a[N], b[N], g[M + 5][M + 5];
int pc, x[M * M + 5], y[M * M + 5], z[M * M + 5], c[M * M + 5], p[M * M + 5];
void sieve(int n) {
  for(int v, i = 2; i <= n; i ++) {
    if(!c[i]) { p[++ pc] = i; c[i] = pc; }
    for(int j = 1; j <= c[i] && (v = i * p[j]) <= n; j ++) c[v] = j;
  }
  x[1] = y[1] = z[1] = 1;
  for(int v, i = 2; i <= n; i ++) {
    v = p[c[i]];
    x[i] = x[i / v] * v; y[i] = y[i / v]; z[i] = z[i / v];
    if(x[i] > y[i]) swap(x[i], y[i]);
    if(y[i] > z[i]) swap(y[i], z[i]);
  }
}
int GCD0(int a, int b) {
  if(!a || !b) return a | b;
  if(p[c[b]] == b) return a % b == 0 ? b : 1;
  if(p[c[a]] == a) return b % a == 0 ? a : 1;
  if(a < b) swap(a, b);
  return g[a % b][b];
}
int GCD(int a, int b) {
  if(a < b) swap(a, b);
  if(b <= M) return GCD0(a, b);
  int res = 1, g;
  g = GCD0(a, x[b]); res *= g; a /= g;
  g = GCD0(a, y[b]); res *= g; a /= g;
  g = GCD0(a, z[b]); res *= g;
  return res;
}
int main() {
  sieve(M * M);
  rep(i, 0, M) g[0][i] = g[i][0] = i ? i : 1;
  rep(i, 1, M) rep(j, i, M) g[i][j] = g[j][i] = g[i][j - i];
  scanf("%d", &n);
  rep(i, 1, n) scanf("%d", a + i);
  rep(i, 1, n) scanf("%d", b + i);
  rep(i, 1, n) {
    int ans = 0, pw = 1;
    rep(j, 1, n) {
      pw = (ll)pw * i % mod;
      ans = (ans + (ll)pw * GCD(a[i], b[j])) % mod;
    }
    printf("%d\n", ans);
  }
  return 0;
}