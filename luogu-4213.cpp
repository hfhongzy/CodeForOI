#include <cstdio>
#include <cstring>
#include <algorithm>
#define fs first
#define sc second
using namespace std;

typedef long long ll;
typedef pair<ll, ll> P;

const int N = 1788115, M = 1250;

int p[N], c, n;
bool tag[N];
ll mu[N], phi[N];
void sieve(int n) {
   phi[1] = mu[1] = 1;
   for(int i = 2; i <= n; i ++) {
      if(!tag[i]) { p[++ c] = i; mu[i] = -1; phi[i] = i - 1; }
      for(int j = 1; j <= c && i * p[j] <= n; j ++) {
         tag[i * p[j]] = 1;
         if(i % p[j] == 0) {
            mu[i * p[j]] = 0;
            phi[i * p[j]] = phi[i] * p[j];
            break ;
         }
         mu[i * p[j]] = - mu[i];
         phi[i * p[j]] = phi[i] * (p[j] - 1);
      }
      mu[i] += mu[i - 1]; phi[i] += phi[i - 1];
   }
}

bool vis[M];
P ans[M];
P calc(unsigned n) {
   if(n < N) return P(phi[n], mu[n]);
   int x = ::n / n;
   if(vis[x]) return ans[x];
   vis[x] = 1;
   P res(n * (n + 1ll) / 2, 1ll), t;
   for(unsigned i = 2, j; i <= n; i = j + 1) {
      j = n / (n / i); t = calc(n / i);
      res.fs -= (j - i + 1) * t.fs;
      res.sc -= (j - i + 1) * t.sc;
   }
   return ans[x] = res;
}
int main() {
   int T; scanf("%d", &T); sieve(N - 1);
   while(T --) {
      scanf("%d", &n);
      P res = calc(n);
      printf("%lld %lld\n", res.fs, res.sc);
      if(T && n >= N) memset(vis, 0, sizeof vis);
   }
   return 0;
}