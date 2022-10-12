#include <algorithm>
#include <cstdio>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

typedef long long ll;

const int N = 1e6 + 5;
const int mod = 1e9 + 7;

int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = (ll) a * a % mod)
      if(b & 1) ans = (ll) ans * a % mod;
   return ans;
}
int n, m, c, p[N], sig[N], pm[N], mu[N], sigS[N], f[N], g[N];
bool tag[N];
void sieve(int n) {
   sig[1] = mu[1] = 1;
   for(int i = 2; i <= n; i ++) {
      if(!tag[i]) {
         p[++ c] = i; mu[i] = mod - 1;
         sig[i] = pm[i] = i + 1;
      }
      for(int j = 1; i * p[j] <= n; j ++) {
         int u = i * p[j]; tag[u] = 1;
         if(i % p[j] == 0) {
            pm[u] = ((ll) pm[i] * p[j] + 1) % mod;
            sig[u] = (ll) sig[i] * qpow(pm[i], mod - 2) % mod * pm[u] % mod;
            break ;
         }
         mu[u] = mod - mu[i]; pm[u] = p[j] + 1;
         sig[u] = (ll) sig[i] * pm[u] % mod;
      }
   }
   rep(i, 1, n) sigS[i] = (sigS[i - 1] + sig[i]) % mod;
   rep(i, 1, n) if(mu[i]) {
      rep(j, 1, n / i) {
         (f[i * j] += 1ll * mu[i] * i % mod * sig[j] % mod * sigS[j] % mod) %= mod;
         (g[i * j] += 1ll * mu[i] * i % mod * sig[j] % mod * sig[j] % mod) %= mod;
      }
   }
   rep(i, 1, n) f[i] = (f[i - 1] + 2ll * i * f[i]) % mod;
   rep(i, 1, n) g[i] = (g[i - 1] + 1ll * i * g[i]) % mod;
   rep(i, 1, n) g[i] = (f[i] - g[i] + mod) % mod;
}
int main() {
   sieve(1e6);
   int test; scanf("%d", &test);
   rep(T, 1, test) {
      int n; scanf("%d", &n);
      printf("Case #%d: %d\n", T, g[n]);
   }
   return 0;
}