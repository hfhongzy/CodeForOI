#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;

typedef long long ll;

const int N = 1e6 + 15;

int c, p[N], m, idx1[N], idx2[N];
bool tag[N];
ll n, sq, pos[N], g[N];
void sieve(int n) {
   sq = n;
   for(int i = 2; i <= n; i ++) {
      if(!tag[i]) p[++ c] = i;
      for(int j = 1; j <= c && i * p[j] <= n; j ++) {
         tag[i * p[j]] = 1;
         if(i % p[j] == 0) break ;
      }
   }
}
int main() {
   scanf("%lld", &n);
   sieve((int) sqrt(n) + 2);
   for(ll l = 1, r; l <= n; l = r + 1) {
      r = n / (n / l);
      pos[++ m] = n / l; g[m] = n / l - 1;
      if(n / l <= sq) idx1[n / l] = m;
      else idx2[r] = m;
   }
   for(int i = 1; i <= c; i ++) {
      for(int j = 1; j <= m && 1ll * p[i] * p[i] <= pos[j]; j ++) {
         ll x = pos[j] / p[i];
         int z = x <= sq ? idx1[x] : idx2[n / x];
         g[j] -= g[z] - i + 1;
      }
   }
   printf("%lld\n", g[1]);
   return 0;
}