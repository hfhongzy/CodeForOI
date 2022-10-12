#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 5005;
const int mod = 1e9 + 7;
const int inv6 = (mod + 1) / 6;
int n;
ll f[N], g[N];
int main() {
  scanf("%d", &n);
  f[0] = g[0] = 1;
  rep(i, 1, n) {
    if((i - 1) % 3 == 0) (f[i] += 2 * f[(i - 1) / 3]) %= mod;
    rep(j, 0, (i - 1) / 2)
      (f[i] += 3 * f[j] * f[i - 2 * j - 1]) %= mod;
    rep(j, 0, i - 1)
      (f[i] += f[j] * g[i - 1 - j]) %= mod;
    f[i] = f[i] * inv6 % mod;
    rep(j, 0, i) (g[i] += f[j] * f[i - j]) %= mod;
  }
  printf("%lld\n", f[n]);
  return 0;
}