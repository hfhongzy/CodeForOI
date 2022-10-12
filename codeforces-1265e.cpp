#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
const int mod = 998244353;
int n, p[N], ip[N], inv[128];
int main() {
  scanf("%d", &n);
  inv[1] = 1;
  rep(i, 2, 100) inv[i] = (ll)inv[mod % i] * (mod - mod / i) % mod;
  rep(i, 1, n) {
    scanf("%d", p + i);
    ip[i] = 100ll * inv[p[i]] % mod;
    p[i] = (ll)p[i] * inv[100] % mod;
  }
  int coef = ip[1];
  rep(i, 2, n) {
    //f[i] = 1/p[i] + f[i + 1] + (1 - p[i])coef/p[i]
    int t = (coef * (mod + 1ll - p[i]) + 1) % mod * ip[i] % mod;
    (coef += t) %= mod;
  }
  printf("%d\n", coef);
  return 0;
}