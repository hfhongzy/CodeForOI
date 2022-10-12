#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 2e4 + 10;
const int M = 510;
bool tag[N];
int p[N], pc, n;
ll a[M][M], f[M * 2], g[M * 2];
void sieve(int n) {
  rep(i, 2, n) {
    if(!tag[i]) p[++ pc] = i;
    for(int v, j = 1; j <= pc && (v = i * p[j]) <= n; j ++) {
      tag[v] = 1;
      if(i % p[j] == 0) break ;
    }
  }
}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return !a || !b ? (a | b) : a / gcd(a, b) * b; }
int main() {
  scanf("%d", &n);
  if(n == 2) { puts("23 10\n4 7\n"); return 0; }
  int o = 0;
  sieve(8000);
  int s = n - 1 - (n % 2 == 0);
  int l = 1, r = s + n + 1;
  for(int i = -s; i <= s; i += 2) {
    o ^= 1;
    g[n + i] = o ? p[l++] : p[r--];
  }
  o = 0;
  for(int i = 2; i <= 2 * n; i += 2) {
    o ^= 1;
    f[i] = o ? p[l++] : p[r--];
  }
  const int dx[] = {0, 1, -1, 0}, dy[] = {1, 0, 0, -1};
  rep(i, 1, n) rep(j, 1, n) if(!(i + j & 1))
    a[i][j] = f[i + j] * g[i - j + n];
  rep(i, 1, n) rep(j, 1, n) if((i + j) & 1) {
    for(int k = 0; k < 4; k ++)
      a[i][j] = lcm(a[i][j], a[i + dx[k]][j + dy[k]]);
    ++a[i][j];
  }
  rep(i, 1, n) rep(j, 1, n)
    printf("%lld%c", a[i][j], " \n"[j == n]);
  return 0;
}