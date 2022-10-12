#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
int n, k, mod, c[N], inv[N], s[N];
void dfs(int d, int l, int r) {
  if(d <= 1 || l == r) { ++ c[r - l + 1]; return ; }
  int m = (l + r) >> 1;
  dfs(d - 1, l, m); dfs(d - 1, m + 1, r);
}
int solve(int n, int m) {
  int res = (ll)inv[2] * n % mod * m % mod;
  rep(i, 1, n) (res += s[i] - s[i + m]) %= mod;
  return (res + mod) % mod;
}
int main() {
  scanf("%d%d%d", &n, &k, &mod);
  inv[1] = 1;
  rep(i, 2, max(4, n)) inv[i] = (mod - mod / i) * (ll)inv[mod % i] % mod;
  rep(i, 1, n) s[i] = (s[i - 1] + inv[i]) % mod;
  dfs(k, 1, n);
  int l = 0;
  rep(i, 1, n) if(c[i]) { l = i; break; }
  int res = (
    (c[l] * (l - 1ll) + c[l + 1] * (l + 1ll)) % mod * l % mod * inv[4]
    + c[l] * (c[l] - 1ll) % mod * inv[2] % mod * solve(l, l)
    + (ll)c[l] * c[l + 1] % mod * solve(l, l + 1)
    + c[l + 1] * (c[l + 1] - 1ll) % mod * inv[2] % mod * solve(l + 1, l + 1)
    ) % mod;
  printf("%d\n", res);
  return 0;
}