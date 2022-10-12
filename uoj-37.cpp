#include <bits/stdc++.h>
#define LOG(FMT...) fprintf(stderr, FMT)
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 15;
const int mod = 1e9 + 7;
int add(int x, int y) { return (x += y) >= mod ? x - mod : x; }
int n, m, pw[N * N], c[1 << N], f[1 << N], u[1 << N], out[1 << N], in[1 << N], e0[1 << N], e12[1 << N];
int main() {
  scanf("%d%d", &n, &m);
  pw[0] = 1;
  for(int i = 1; i <= m; i ++) pw[i] = add(pw[i - 1], pw[i - 1]);
  int x, y;
  for(int i = 0; i < m; i ++) {
    scanf("%d%d", &x, &y);
    x = 1 << (x - 1); y = 1 << (y - 1);
    out[x] |= y; in[y] |= x;
  }
  for(int i = 1; i < (1 << n); i ++)
    c[i] = c[i & (i - 1)] + 1;
  for(int i = 1; i < (1 << n); i ++) {
    int v = i & (-i);
    e0[i] = e0[i & (i - 1)] + c[out[v] & i] + c[in[v] & i];
  }
  for(int i = 1; i < (1 << n); i ++) {
    if(c[i] == 1) { f[i] = 1; u[i] = mod - 1; continue ; }
    int v = i & (i - 1);
    f[i] = pw[e0[i]];
    e12[i] = 0;
    for(int j = v; j; j = (j - 1) & i) {
      int l = i ^ j; l &= -l;
      e12[j] = e12[j | l] - c[out[l] & (i ^ j)] + c[in[l] & j];
      f[i] = (f[i] + (ll)u[j] * pw[e12[j] + e0[i ^ j]]) % mod;
    }
    for(int j = v; j; j = (j - 1) & v) {
      u[i] = (u[i] - (ll)u[j] * f[i ^ j]) % mod;
    }
    if(u[i] < 0) u[i] += mod;
    f[i] = add(f[i], u[i]);
    u[i] = add(u[i], mod - f[i]);
  }
  printf("%d\n", f[(1 << n) - 1]);
  return 0;
}