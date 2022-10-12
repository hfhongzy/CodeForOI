#include <algorithm>
#include <cstdio>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

typedef long long ll;

const int N = 1e6 + 5, M = 1e3 + 10;
const int mod = 1e9 + 7;
const int inv6 = 166666668;

int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = (ll) a * a % mod)
      if(b & 1) ans = (ll) ans * a % mod;
   return ans;
}
int n, c, p[N], mu[N], f[N];
bool tag[N];
int F(int n) {
   return (1ll * n * n - 3 * n + 2) % mod;
}
int S1(int n) {
   return n * (n + 1ll) / 2 % mod;
}
int S2(int n) {
   return n * (n + 1ll) % mod * (2 * n + 1) % mod * inv6 % mod;
}
void sieve(int n) {
   mu[1] = 1;
   for(int i = 2; i <= n; i ++) {
      if(!tag[i]) { p[++ c] = i; mu[i] = -1; }
      for(int j = 1; i * p[j] <= n; j ++) {
         int u = i * p[j]; tag[u] = 1;
         if(i % p[j] == 0) break ;
         mu[u] = - mu[i];
      }
   }
   rep(i, 1, n) {
      rep(j, 1, n / i) if(mu[j]) {
         (f[i * j] += mu[j] * F(i)) %= mod;
      }
   }
   rep(i, 1, n) (f[i] += f[i - 1]) %= mod;
}
bool vis[M];
int ans[M];
int Sum(int u) {
   if(u < N) return f[u];
   int x = n / u;
   if(vis[x]) return ans[x];
   vis[x] = 1;
   int &res = ans[x]; res = (S2(u) - 3ll * S1(u) + 2 * u) % mod;
   for(int i = 2, j; i <= u; i = j + 1) {
      j = u / (u / i);
      (res -= (j - i + 1ll) * Sum(u / i) % mod) %= mod;
   }
   return res;
}
int main() {
   sieve(1e6);
   int test; scanf("%d", &test);
   while(test --) {
      scanf("%d", &n);
      rep(i, 0, M - 1) vis[i] = 0;
      printf("%d\n", (Sum(n) + mod) % mod);
   }
   return 0;
}