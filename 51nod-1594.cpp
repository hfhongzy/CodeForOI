#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

typedef long long ll;

const int N = 2e6 + 10;

int p[N], c, n, mu[N], a[N], phi[N];
ll g[N], f[N];
bool tag[N];
void sieve(int n) {
   mu[1] = phi[1] = 1;
   for(int i = 2; i <= n; i ++) {
      if(!tag[i]) { p[++ c] = i; mu[i] = -1; phi[i] = i - 1; }
      for(int j = 1; j <= c && i * p[j] <= n; j ++) {
         tag[i * p[j]] = 1;
         if(i % p[j] == 0) {
            phi[i * p[j]] = phi[i] * p[j];
            break ;
         }
         mu[i * p[j]] = - mu[i];
         phi[i * p[j]] = phi[i] * (p[j] - 1);
      }
   }
}
// int gcd(int x, int y) { return !y ? x : gcd(y, x % y); }
// ll force(ll n) {
//    ll ans = 0;
//    rep(i, 1, n) rep(j, 1, n) ans += phi[gcd(phi[i], phi[j])];
//    return ans;
// }
int main() {
   int test; scanf("%d", &test); sieve(N - 1);
   while(test --) {
      scanf("%d", &n); //printf("force = %lld\n", force(n));
      rep(i, 1, n) a[i] = 0;
      rep(i, 1, n) a[phi[i]] ++;
      rep(i, 1, n) {
         g[i] = 0;
         for(int j = i; j <= n; j += i) {
            g[i] += a[j];
         }
         g[i] *= g[i];
      }
      rep(i, 1, n) {
         f[i] = 0;
         for(int j = i; j <= n; j += i) {
            f[i] += mu[j / i] * g[j];
         }
      }
      ll ans = 0;
      rep(i, 1, n) {
         ans += phi[i] * f[i];
      }
      printf("%lld\n", ans);
   }
   return 0;
}