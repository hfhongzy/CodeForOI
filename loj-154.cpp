#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
char gc() {
  return getchar();
  static char buf[1 << 17], *S, *T;
  if(S == T) T = (S = buf) + fread(buf, 1, 1 << 17, stdin);
  return S == T ? EOF : *S ++;
}
template<class T> void read(T &x) {
  x = 0; char c = gc(); bool na = 0;
  for(; c < '0' || c > '9'; c = gc()) na |= c == '-';
  for(; c >= '0' && c <= '9'; c = gc()) x = x * 10 + (c & 15);
  if(na) x = -x;
}
const int mod = 998244353;
int n, m, k, c[1 << 21][22], cnt[1 << 21], inv[24], f[1 << 21][22];
int add(int a, int b) { return (a += b) >= mod ? a - mod : a; }
int main() {
  read(n); read(m); read(k);
  for(int i = 1; i < (1 << n); i ++) cnt[i] = cnt[i & (i - 1)] + 1;
  int s;
  for(int i = 0; i < m; i ++) { read(s); c[s][cnt[s]] ++; }
  for(int i = 1; i <= n; i ++) inv[i] = i > 1 ? (ll)inv[mod % i] * (mod - mod / i) % mod : 1;
  for(int i = 2; i <= n; i ++) inv[i] = (ll)inv[i] * inv[i - 1] % mod;
  for(int i = 1; i < (1 << n); i <<= 1)
  for(int j = 0; j < (1 << n); j += i << 1)
    for(int k = 0; k < i; k ++)
      for(int u = 1; u <= n; u ++)
        c[j + i + k][u] = add(c[j + i + k][u], c[j + k][u]);
  for(int i = 0; i < (1 << n); i ++) f[i][0] = 1;
  int ans = 0;
  for(int i = 1; i <= k; i ++) {
    for(int k = 0; k < (1 << n); k ++) {
      for(int u = n; u >= 1; u --) {
        ull r = 0;
        for(int v = 0; v < u; v ++) {
          r += static_cast<ull>(f[k][v]) * c[k][u - v];
        }
        f[k][u] = r % mod;
      }
    }
    if(i == 1) {
      for(int k = 0; k < (1 << n); k ++)
        f[k][0] = 0;
    }
    ll cur = 0;
    for(int i = 0; i < (1 << n); i ++) {
      cur += (n - cnt[i]) & 1 ? - f[i][n] : f[i][n];
    }
    cur = cur % mod + mod;
    ans = (ans + inv[i] * cur) % mod;
  }
  printf("%d\n", ans);
  return 0;
}