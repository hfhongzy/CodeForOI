#include <cstdio>
#include <cstring>
#include <algorithm>
#define fs first
#define sc second
using namespace std;

typedef long long ll;

const int N = 4641590, M = 2160;
const int mod = 1e9 + 7, inv2 = (mod + 1) >> 1, inv6 = 166666668;

int p[N], c, phi[N];
bool tag[N];
void sieve(int n) {
   phi[1] = 1;
   for(int i = 2; i <= n; i ++) {
      if(!tag[i]) { p[++ c] = i; phi[i] = i - 1; }
      for(int j = 1; j <= c && i * p[j] <= n; j ++) {
         tag[i * p[j]] = 1;
         if(i % p[j] == 0) {
            phi[i * p[j]] = phi[i] * p[j]; break ;
         }
         phi[i * p[j]] = phi[i] * (p[j] - 1);
      }
      phi[i] = (1ll * i * i % mod * phi[i] + phi[i - 1]) % mod;
   }
}
ll n;
int ans[M];
bool vis[M];
int S1(ll n) {
   n %= mod;
   return n * (n + 1) % mod * inv2 % mod;
}
int S2(ll n) {
   n %= mod;
   return n * (n + 1) % mod * (2 * n + 1) % mod * inv6 % mod;
}
int S3(ll n) {
   n %= mod;
   n = n * (n + 1) % mod * inv2 % mod;
   return n * n % mod;
}
int solve(ll n) {
   if(n < N) return phi[n];
   int x = ::n / n;
   if(vis[x]) return ans[x];
   vis[x] = 1;
   int &z = ans[x]; z = S3(n);
   for(ll l = 2, r; l <= n; l = r + 1) {
      r = n / (n / l);
      z = (z + (S2(l - 1) - S2(r)) * (ll) solve(n / l)) % mod;
   }
   if(z < 0) z += mod;
   return z;
}
int main() {
   sieve(N - 1);
   scanf("%lld", &n);
   int ans = 0;
   for(ll l = 1, r; l <= n; l = r + 1) {
      r = n / (n / l);
      ans = (ans + (S1(r) - S1(l - 1)) * (ll) solve(n / l)) % mod;
   }
   if(ans < 0) ans += mod;
   printf("%d\n", ans);
   return 0;
}