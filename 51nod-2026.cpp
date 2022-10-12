#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long ll;

const int N = 1e6 + 10, M = 1005, mod = 1e9 + 7;

int p[N], c, n, mu[N];
bool tag[N];
void sieve(int n) {
   mu[1] = 1;
   for(int i = 2; i <= n; i ++) {
      if(!tag[i]) { p[++ c] = i; mu[i] = -1; }
      for(int j = 1; j <= c && i * p[j] <= n; j ++) {
         tag[i * p[j]] = 1;
         if(i % p[j] == 0) break ;
         mu[i * p[j]] = - mu[i];
      }
      mu[i] *= i; (mu[i] += mu[i - 1]) %= mod;
   }
}
int ans[M];
bool vis[M];
int S1(int n) {
   return n * (n + 1ll) / 2 % mod;
}
int solve(int n) {
   if(n < N) return mu[n];
   int x = ::n / n;
   if(vis[x]) return ans[x];
   vis[x] = 1;
   int &z = ans[x]; z = 1;
   for(int l = 2, r; l <= n; l = r + 1) {
      r = n / (n / l);
      z = (z + (S1(l - 1) - S1(r)) * (ll) solve(n / l)) % mod;
   }
   return z;
}
int main() {
   sieve(N - 1);
   scanf("%d", &n);
   int ans = 0, la = 0, cur = 0;
   for(int l = 1, r; l <= n; l = r + 1, la = cur) {
      r = n / (n / l); cur = solve(r);
      ans = (ans + (cur - la + 0ll) * (n / l)) % mod;
   }
   if(ans < 0) ans += mod;
   ans = 1ll * ans * ans % mod;
   printf("%d\n", ans);
   return 0;
}